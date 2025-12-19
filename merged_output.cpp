/*
 * 合并的源文件
 * 来源目录: ./src
 * 文件数量: 29
 * 生成时间: 2025-12-10 20:46:05
 */


/* ============================================ */
/* 文件: AI.cpp */
/* ============================================ */

#include "AI.h"

#include <random>

AI::AI() {}

Pos AI::calculateMove(Board& board, PieceType aiPiece) {
    // @todo 根据棋盘分数图取最大值算出最佳位置
    return maxScoreMove(board, aiPiece);
}

Pos AI::randomMove(Board& board) {
    std::random_device rd;  // 使用硬件熵源获取随机种子
    std::mt19937 gen(rd()); // 使用Mersenne Twister引擎
    std::uniform_int_distribution<> distrib(0, Board::BOARD_SIZE); // 生成[1,100]的整数
    
    Pos pos;
    do {
        pos = Pos(distrib(gen), distrib(gen));
    } while (!board.isEmpty(pos));

    return pos;
}

Pos AI::maxScoreMove(Board& board, PieceType aiPiece) {
    return genScoreMap(board, aiPiece).findMax();
}

ScoreMap AI::genScoreMap(Board& board, PieceType aiPiece) {
    ScoreMap scoreMap;
    scoreMap.initScoreMap();
    for (int x = 0; x < Board::BOARD_SIZE; x++) {
        for (int y = 0; y < Board::BOARD_SIZE; y++) {
            Pos pos(x, y);
            if (!board.isEmpty(pos)) { //如果位置已经有棋子了，不能重复落子
                scoreMap.setScore(pos, -1);
            } else {
                scoreMap.setScore(pos, getPosScore(board, pos, aiPiece) + scoreMap.getScore(pos));
            }
        }
    }
    return scoreMap;
}


int AI::scorePattern(const PatternType pattern) {
    switch (pattern)
    {
    case PatternType::FIVE:
        return 1000;
    case PatternType::OVERLINE:
        return 1000;
    case PatternType::LIVE_FOUR:
        return 800;
    case PatternType::SLEEP_FOUR:
        return 600;
    case PatternType::BLOCK_FOUR:
        return 0;
    case PatternType::LIVE_THREE:
        return 500;
    case PatternType::SLEEP_THREE:
        return 300;
    case PatternType::BLOCK_THREE:
        return 0;
    case PatternType::LIVE_TWO:
        return 100;
    case PatternType::SLEEP_TWO:
        return 20;
    case PatternType::BLOCK_TWO:
        return 0;
    case PatternType::ONE:
        return 1;
    default:
        break;
    }
}

int AI::getPosScore(Board& board, Pos pos, PieceType aiPiece) {
    int score = 0;
    for (auto lineInfo : board.getAllLines(pos, aiPiece)) { //考虑自己走哪里能赢
        score += scorePattern(Board::parsePatten(lineInfo));
    }
    for (auto lineInfo : board.getAllLines(pos, Board::opponentOf(aiPiece))) { //考虑如何阻止对方赢
        score += 0.9 * scorePattern(Board::parsePatten(lineInfo)); 
    }
    return score;
}

/* ============================================ */
/* 文件: AI.h */
/* ============================================ */

#pragma once

#include "Board.h"
#include "ScoreMap.h"

class AI
{
public:
    AI();
    /**
     * @brief 给出下一步棋的位置
     * @param aiPiece   调用方的持子类型，从BLACK, WHITE中选择
     */
    Pos calculateMove(Board& board, PieceType aiPiece);

private:
    /**
     * @brief 一个完全随机的下棋函数，当场上棋子较多时可能比较费时
     * @see 引自DeepSeek
     */
    Pos randomMove(Board& board);
    /**
     * @brief 根据分数图选取分数最大的位置落子
     */
    Pos maxScoreMove(Board& board, PieceType aiPiece);
    /**
     * @brief 根据给定棋盘和持子方生成分数图
     */
    ScoreMap genScoreMap(Board& board, PieceType aiPiece);
    /**
     * @brief 事实上，当AI下棋的时候，它不需要每次都更新所有的ScoreMap，而只需要更新新落子附近的即可
     * @todo
     */
    void updateScoreMap(ScoreMap& scoreMap);
    static int scorePattern(const PatternType pattern);
    static int getPosScore(Board& board, Pos pos, PieceType aiPiece);
};

/* ============================================ */
/* 文件: AIPlayer.cpp */
/* ============================================ */

#include "AIPlayer.h"

PlayerAction AIPlayer::getAction(Board& board, PieceType type) {
    return {ActionType::PLACE_PIECE, calculateMove(board, type)};
}

/* ============================================ */
/* 文件: AIPlayer.h */
/* ============================================ */

#pragma once

#include "Player.h"

class AIPlayer : public Player
{
public:
    PlayerAction getAction(Board& board, PieceType type) override;
};

/* ============================================ */
/* 文件: Board.cpp */
/* ============================================ */

#include <array>
#include <sstream>
#include <iomanip>

#include "Board.h"
#include "GameTypes.h"

Board::Board() {
    clearBoard();
}

Board Board::createEmptyBoard() {
    return Board();
}

int Board::rowToPosY(int row) {
    return BOARD_SIZE - row;
}

bool Board::isOnBoard(Pos pos) {
    return pos.x >= 0 && pos.x < BOARD_SIZE && pos.y >= 0 && pos.y < BOARD_SIZE;
}

PieceType Board::getPos(Pos pos) const {
    return board[pos.x][pos.y];
}

bool Board::setPos(Pos pos, PieceType type) {
    board[pos.x][pos.y] = type;
    return true;
}

bool Board::isEmpty(Pos pos) {
    return getPos(pos) == PieceType::EMPTY;
}

LineInfo Board::getLongestLine(Pos pos) const {
    return getLongestLine(pos, getPos(pos));
}

LineInfo Board::getLongestLine(Pos pos, PieceType type) const {
    LineInfo longestLine;
    for (LineInfo info : getAllLines(pos, type)) {
        if (info.length >= longestLine.length) {
            longestLine = info;
        }
    }
    return longestLine;
}


std::array<LineInfo, 4> Board::getAllLines(Pos pos) const {
    return getAllLines(pos, getPos(pos));
}

std::array<LineInfo, 4> Board::getAllLines(Pos pos, PieceType type) const {
    std::array<LineInfo, 4> result;
    result[0] = checkLine(pos, Dir::HORIZONTAL, type);
    result[1] = checkLine(pos, Dir::VERTICAL, type);
    result[2] = checkLine(pos, Dir::RIGHTUP, type);
    result[3] = checkLine(pos, Dir::RIGHTDOWN, type);
    return result;
}

LineInfo Board::checkLine(Pos pos, Dir dir) const {
    return mergeLineInfo(checkLineToDir(pos, dir, false), checkLineToDir(pos, dir, true));
}

LineInfo Board::checkLine(Pos pos, Dir dir, PieceType type) const {
    return mergeLineInfo(checkLineToDir(pos, dir, false, type), checkLineToDir(pos, dir, true, type));
}

LineInfo Board::checkLineToDir(Pos pos, Dir dir, bool isForward) const {
    return checkLineToDir(pos, dir, isForward, getPos(pos));
}

LineInfo Board::checkLineToDir(Pos pos, Dir dir, bool isForward, PieceType type) const {
    LineInfo info;
    info.dir = dir;
    if (type == PieceType::EMPTY) {
        return info;
    } else {
        int forward = (isForward) ? 1 : -1;
        Pos currPos = pos; //当前检查的位置
        info.length += 1;
        currPos += (Pos::toPos(dir) *= forward);
        for (; isOnBoard(currPos) && getPos(currPos) == type; currPos += (Pos::toPos(dir) *= forward)) {
            info.length += 1;
        }
        if (isOnBoard(currPos) && getPos(currPos) == PieceType::EMPTY) {
            info.openEnds[0] = true;
            info.openEnds[1] = true;
        }
        return info;
    }
}

PatternType Board::parsePatten(LineInfo lineInfo) {
    int openEnds = 0;
    if (lineInfo.openEnds[0] == true) {openEnds += 1;}
    if (lineInfo.openEnds[1] == true) {openEnds += 1;}
    switch (lineInfo.length)
    {
    case 5:
        return PatternType::FIVE;
    case 4:
        switch (openEnds)
        {
        case 2:
            return PatternType::LIVE_FOUR;
        case 1:
            return PatternType::SLEEP_FOUR;
        case 0:
            return PatternType::BLOCK_FOUR;
        }
    case 3:
        switch (openEnds)
        {
        case 2:
            return PatternType::LIVE_THREE;
        case 1:
            return PatternType::SLEEP_THREE;
        case 0:
            return PatternType::BLOCK_THREE;
        }
    case 2:
        switch (openEnds)
        {
        case 2:
            return PatternType::LIVE_TWO;
        case 1:
            return PatternType::SLEEP_TWO;
        case 0:
            return PatternType::BLOCK_TWO;
        }
    case 1:
        return PatternType::ONE;   
    default:
        if (lineInfo.length > 5) {
            return PatternType::OVERLINE;
        }
        return PatternType::INVALID;
    }
}

void Board::clearBoard() {
    for (int i = 0; i < Board::BOARD_SIZE; i++) {
        for (int j = 0; j < Board::BOARD_SIZE; j++) {
            setPos(Pos(i, j), PieceType::EMPTY);
        }
    }
}

LineInfo Board::mergeLineInfo(LineInfo info1, LineInfo info2) const {
    LineInfo info;
    if (info1.dir != info2.dir) {
        throw std::invalid_argument("两个参数的Dir必须一致!");
    }
    info.dir = info1.dir;
    info.length = info1.length + info2.length - 1;
    info.openEnds[0] = info1.openEnds[0];
    info.openEnds[1] = info2.openEnds[0];
    return info;
}

PieceType Board::opponentOf(PieceType type) {
    return (type == PieceType::BLACK) ? PieceType::WHITE : PieceType::BLACK;
}

std::string Board::toString() const {
    std::stringstream ss;
    for (int i = BOARD_SIZE; i >= 1; i--) {
        ss << std::setw(2) << i << toStringRow(i) << std::endl;
    }
    ss << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        ss << " " << char('A' + i) << " ";
    }
    return ss.str();
}

std::string Board::toStringRow(int row) const {
    std::stringstream ss;
    for (int i = 0; i < BOARD_SIZE; i++) {
        switch (getPos(Pos(i, BOARD_SIZE - row)))
        {
        case PieceType::EMPTY:
            ss << " . ";
            break;
        case PieceType::BLACK:
            ss << " ● ";
            break;
        case PieceType::WHITE:
            ss << " ○ ";
            break;
        default:
            ss << " ? ";
            break;
        }
    }
    return ss.str();
}

/* ============================================ */
/* 文件: Board.h */
/* ============================================ */

#pragma once

#include "Object.h"
#include <array>
#include "GameTypes.h"
#include "Pos.h"

enum class PatternType
{
    FIVE,               // 连五
    OVERLINE,
    LIVE_FOUR,          // 活四
    SLEEP_FOUR,         // 冲四/眠四
    LIVE_THREE,         // 活三
    SLEEP_THREE,        // 眠三
    LIVE_TWO,           // 活二
    SLEEP_TWO,          // 眠二
    ONE,

    // 防守相关
    BLOCK_FOUR,         // 挡四
    BLOCK_THREE,
    BLOCK_TWO,
    INVALID
};

/**
 * 这个类表示连子的结构，如三连，四连以及死活等
 */
class LineInfo : public Object
{
public:
    int length = 0;
    bool openEnds[2] = {false, false};
    Dir dir;
    std::string toString() const override {
        std::string str = "LineInfo@";
        str += "length: " + std::to_string(length) + "\n";
        str += "openEnds: " + std::to_string(openEnds[0]) + ", " + std::to_string(openEnds[1]) + "\n";
        str += "Direction: " + Pos::toPos(dir).toString();
        return str;
    }
};

/**
 * 这个类代表一个棋盘
 */
class Board : public Object
{
public:
    /* 棋盘长度为15 */
    static const int BOARD_SIZE = 15;
    /* 获取空棋盘的工厂方法 */
    static Board createEmptyBoard();
    /* 将棋盘上的行号转化为坐标y值 */
    static int rowToPosY(int row);
    /* 判断给定坐标是否在棋盘上 */
    static bool isOnBoard(Pos pos);
    /* 访问棋盘数据 */
    PieceType getPos(Pos pos) const;
    /* 设置棋盘数据，返回值表示是否设置成功 */
    bool setPos(Pos pos, PieceType type);
    /* 返回该位置是否没有棋子 */
    bool isEmpty(Pos pos);
    /**
     * @brief 检查给定位置连子数量最多的方向
     */
    LineInfo getLongestLine(Pos pos) const;
    /**
     * @brief 检查如果给定位置是给定类型，连子数量最多的方向
     */
    LineInfo getLongestLine(Pos pos, PieceType type) const;
    /**
     * @brief 获得给定位置所有方向的连子情况
     */
    std::array<LineInfo, 4> getAllLines(Pos pos) const;
    /**
     * @brief 获得如果给定位置是给定类型，所有方向的连子情况
     */
    std::array<LineInfo, 4> getAllLines(Pos pos, PieceType type) const;
    /** 
     * @brief 检查给定位置在给定方向的连子数量，这里的方向包含两边
     * @param dir 一共四个方向HORIZONTAL, VAERTICAL, RIGHTUP, RIGHTDOWN
     */
    LineInfo checkLine(Pos pos, Dir dir) const;
    /** 
     * @brief 检查如果给定位置是给定类型棋子，在给定方向的连子数量，这里的方向包含两边
     * @param dir 一共四个方向HORIZONTAL, VAERTICAL, RIGHTUP, RIGHTDOWN
     */
    LineInfo checkLine(Pos pos, Dir dir, PieceType type) const;
    /**
     * @brief 检查给定位置在给定方向的连子数量
     * @param dir           只能在HERIZONTAL, VERTICAL, RIGHTUP, RIGHTDOWN四个方向中选择
     * @param isForward     以Pos坐标增大的方向为前方，说明是往前统计还是往后统计, 如果是true, 向前统计
     * @return              返回值length包含子本身，如果在该方向上被堵死，openEnds全为false，若没有，则全为true
     */
    LineInfo checkLineToDir(Pos pos, Dir dir, bool isForward) const;
    /**
     * @brief 检查给定位置如果是给定棋子类型，则在给定方向的连子数量
     * @param dir           只能在HERIZONTAL, VERTICAL, RIGHTUP, RIGHTDOWN四个方向中选择
     * @param isForward     以Pos坐标增大的方向为前方，说明是往前统计还是往后统计, 如果是true, 向前统计
     * @param type          仅支持BLACK, WHITE两种类型
     * @return              返回值length包含子本身，如果在该方向上被堵死，openEnds全为false，若没有，则全为true
     */
    LineInfo checkLineToDir(Pos pos, Dir dir, bool isForward, PieceType type) const;
    static PatternType parsePatten(LineInfo lineInfo);
    static PieceType opponentOf(PieceType type);
    std::string toString() const override;

private:
    /* 棋盘数据用PieceType枚举存储，0代表空位，1代表黑子，2代表白子 */
    std::array<std::array<PieceType, BOARD_SIZE>, BOARD_SIZE> board;
    Board();
    /* 清空棋盘 */
    void clearBoard();
    /* 将Pos两边的连子情况合并 */
    LineInfo mergeLineInfo(LineInfo info1, LineInfo info2) const;
    std::string toStringRow(int row) const;
};

/* ============================================ */
/* 文件: ConsoleInput.cpp */
/* ============================================ */

#include <iostream>
#include <algorithm>
#include <regex>

#include "ConsoleInput.h"
#include "Board.h"

InputResult ConsoleInput::getMenuInput() {
    std::string input;
    std::cout << "▷ ";
    std::getline(std::cin, input);
    return parseMenuInput(input);
}

InputResult ConsoleInput::parseMenuInput(const std::string& input) {
    InputResult result;
    int n;

    if (input.empty()) {
        result.command = InputCommand::INVALID;
        return result;
    }

    std::string lowerInput = toLower(input);
    if (lowerInput == "quit" || lowerInput == "q") {
        result.command = InputCommand::QUIT;
    } else  if (parseInt(lowerInput, n)) {
        result.command = InputCommand::SELECT_FROM_MENU;
        result.order = n;
    } else {
        result.command = InputCommand::INVALID;
    }

    return result;
}

InputResult ConsoleInput::getInput() {
    std::string input;
    std::cout << "▷ ";
    std::getline(std::cin, input);
    return parseInput(input);
}

std::string ConsoleInput::getInput(const std::string& str) {
    std::string input;
    std::cout << str << std::endl;
    std::cout << "▷ ";
    std::getline(std::cin, input);
    return input;
}

InputResult ConsoleInput::parseInput(const std::string& input) {
    InputResult result;
    int n;
    char c;

    if (input.empty()) {
        result.command = InputCommand::INVALID;
        return result;
    }

    std::string lowerInput = toLower(input);
    if (lowerInput == "quit" || lowerInput == "q") {
        result.command = InputCommand::QUIT;
    } else  if (parseStringRegex(lowerInput, c, n)) {
        result.command = InputCommand::PLACE_PIECE;
        result.pos = parsePos(c, n);
    } else {
        result.command = InputCommand::INVALID;
    }

    return result;
}

Pos ConsoleInput::parsePos(const char& c, const int& num) {
    Pos pos;
    pos.x = c - 'a';
    pos.y = Board::rowToPosY(num);
    return pos;
}

std::string ConsoleInput::toLower(const std::string& str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });
    return lower;
}

bool ConsoleInput::parseStringRegex(const std::string& str, char& c, int& num) {
    std::regex pattern1("^([a-zA-Z])(\\d+)$");
    std::regex pattern2("^(\\d+)([a-zA-Z])$");
    std::smatch matches;
    
    if (std::regex_match(str, matches, pattern1)) {
        c = matches[1].str()[0];  // 获取字符
        num = std::stoi(matches[2].str());  // 获取数字
        return true;
    } else if (std::regex_match(str, matches, pattern2)) {
        c = matches[2].str()[0];  // 获取字符
        num = std::stoi(matches[1].str());  // 获取数字
        return true;
    }
    return false;
}

bool ConsoleInput::parseInt(const std::string& str, int& num) {
    std::regex pattern("^\\d+$");
    std::smatch matches;
    
    if (std::regex_match(str, matches, pattern)) {
        num = std::stoi(matches[1].str());  // 获取数字
        return true;
    }
    return false;
}

/* ============================================ */
/* 文件: ConsoleInput.h */
/* ============================================ */

#pragma once

#include "InputDevice.h"

class ConsoleInput : public InputDevice
{
public:
    ConsoleInput() = default;
    ///~ConsoleInput() override = default;
    InputResult getMenuInput() override;
    InputResult getInput() override;
    std::string getInput(const std::string& str) override;

private:
    /* 解析字符串输入 */
    InputResult parseMenuInput(const std::string& input);
    /* 解析字符串输入 */
    InputResult parseInput(const std::string& input);
    /* 将字符和数字输入解析成棋盘坐标 */
    Pos parsePos(const char& c, const int& num);
    /* 将字符串格式化为小写字母，参考自DeepSeek */
    std::string toLower(const std::string& str);
    /* 如果可以的话，将字符串解析为一个数字和一个字母的组合，不分先后，并返回true */
    bool parseStringRegex(const std::string& str, char& c, int& num);
    /* 如果可以的话，将字符串解析为纯数字，并返回true */
    bool parseInt(const std::string& str, int& num);
};

/* ============================================ */
/* 文件: ConsoleUI.cpp */
/* ============================================ */

#include "ConsoleUI.h"

#include <iostream>
#include <iomanip>

#include "Game.h"
#include "Pos.h"

void ConsoleUI::clearScreen() {
    // ANSI 转义码：\033[2J 清屏，\033[H 光标移到左上角
    std::cout << "\033[2J\033[H";
}

void ConsoleUI::displayStartMenu(GameConfig config) {
    std::cout << "======================================" << std::endl;
    std::cout << "=             五子棋小游戏            =" << std::endl;
    std::cout << "=               @copyright 韩书钰     =" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "==============开始菜单================" << std::endl;
    std::cout << "1.开始游戏" << std::endl;
    std::cout << "2.玩家设置                AI" << std::endl;
    std::cout << "      Player1            " << config.player1IsAI << std::endl;
    std::cout << "      Player2            " << std::endl;
    std::cout << "3.退出游戏" << std::endl;
}

void ConsoleUI::displayBoard(Board& board) {
    std::cout << board.toString() << std::endl;
}

void ConsoleUI::print(const std::string& str) {
    std::cout << str << std::endl;
}

/* ============================================ */
/* 文件: ConsoleUI.h */
/* ============================================ */

#pragma once

#include "Board.h"
#include "GameConfig.h"

class ConsoleUI
{
public:
    /* 清屏 */
    static void clearScreen();
    /* 展示开始菜单 */
    static void displayStartMenu(GameConfig config);
    /* 展示给定的棋盘 */
    static void displayBoard(Board& board);
    /* 输出信息 */
    static void print(const std::string& str);

private:
};

/* ============================================ */
/* 文件: Game.cpp */
/* ============================================ */

#include "Game.h"
#include "Board.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

Game::Game(std::unique_ptr<Player> player1, std::unique_ptr<Player> player2) : board(Board::createEmptyBoard()), judge(Judge()) {
    this->player1 = std::move(player1);
    this->player2 = std::move(player2);
    currentPlayer = this->player1.get();
    state = GameState::PLAYING;
}

GameState Game::run() {
    PlayerAction action = currentPlayer->getAction(board, getPieceType(currentPlayer));
    switch (action.type)
    {
    case ActionType::QUIT:
        state = GameState::QUIT;
        break;
    case ActionType::PLACE_PIECE:
        if (placePiece(action.pos, currentPlayer)) {
            switch (judge.ckeckWin(board, action.pos))
            {
            case GameResult::NO_WINNER:
                changePlayer();
                break;
            case GameResult::BLACK_WIN:
                state = GameState::BLACK_WIN;
                break;
            case GameResult::WHITE_WIN:
                state = GameState::WHITE_WIN;
                break;
            case GameResult::DRAW:
                state = GameState::DRAW;
                break;
            }
        } else {
            setMessage("不能在该处落子！");
        }
        break;
    case ActionType::INVALID:
        setMessage("非法输入");
        break;
    default:
        break;
    }
    return state;   
}

Board& Game::getBoard() {
    return board;
}

std::string& Game::getMessage() {
    return message;
}

PieceType Game::getPieceType(Player* player) {
    return (player == player1.get()) ? PieceType::BLACK : PieceType::WHITE;
}

bool Game::placePiece(Pos pos, Player* player) {
    if (judge.isValidMove(board, pos)) {
        board.setPos(pos, getPieceType(player));
        return true;
    }
    return false;
}

void Game::changePlayer() {
    currentPlayer = (currentPlayer == player1.get()) ? player2.get() : player1.get();
}

void Game::setMessage(const std::string& msg) {
    message = msg;
}

/* ============================================ */
/* 文件: Game.h */
/* ============================================ */

#pragma once

#include <iostream>
#include <memory>

#include "Board.h"
#include "Judge.h"
#include "Player.h"
#include "ConsoleUI.h"
#include "InputDevice.h"

enum class GameState
{
    PLAYING,
    BLACK_WIN,
    WHITE_WIN,
    DRAW,
    QUIT
};

class Game
{
public:
    Game(std::unique_ptr<Player> player1, std::unique_ptr<Player> player2);
    GameState run();
    Board& getBoard();
    std::string& getMessage();

private:
    Board board;
    Judge judge;
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    Player* currentPlayer;
    GameState state;
    std::string message;
    

    /**
     * @brief player1执黑棋，player2执白棋
     */
    PieceType getPieceType(Player* player);

    bool placePiece(const Pos pos, Player* Player);
    /**
     * @brief 轮换正在下棋的玩家
     */
    void changePlayer();
    void setMessage(const std::string& msg);
};

/* ============================================ */
/* 文件: GameConfig.h */
/* ============================================ */

#pragma once

#include "Object.h"

#include <string>

/**
 * @brief 这个类包含了一局游戏需要的所有设置
 */
class GameConfig : public Object
{
public:
    std::string player1Name;
    std::string player2Name;
    bool player1IsAI;
    bool player2IsAI;

    GameConfig(std::string player1Name = "Player1", std::string player2Name = "Player2",
         bool player1IsAI = false, bool player2IsAI = false) : 
         player1Name(player1Name), player1IsAI(player1IsAI), player2Name(player2Name), player2IsAI(player2IsAI) {};
};

/* ============================================ */
/* 文件: GameController.cpp */
/* ============================================ */

#include "GameController.h"

#include "Game.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

GameController::GameController(ConsoleUI& ui, InputDevice& input) : ui(ui), input(input) {
    state = GameControllerState::MAIN_MENU;
}

GameConfig GameController::getGameConfig() {
    GameConfig config = createDefaultConfig();
    bool isAI;
    isAI = input.getInput("Player1 AI(0/1)?") == "1";
    config.player1IsAI = isAI;
    isAI = input.getInput("Player2 AI(0/1)?") == "1";
    config.player2IsAI = isAI;
    return config;
}

Game GameController::initGame(GameConfig config) {
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    if (config.player1IsAI) {
        player1 = std::make_unique<AIPlayer>();
    } else {
        player1 = std::make_unique<HumanPlayer>(input);
    }
    if (config.player2IsAI) {
        player2 = std::make_unique<AIPlayer>();
    } else {
        player2 = std::make_unique<HumanPlayer>(input);
    }
    return Game(std::move(player1), std::move(player2));
}

/*
Game GameController::initGame() {
    GameConfig config = createDefaultConfig();
    while (state == GameControllerState::MAIN_MENU) {
        ui.displayStartMenu(config);
        InputResult result = input.getMenuInput();
        switch (result.command)
        {
        case InputCommand::SELECT_FROM_MENU:
            break;
        }
    }
}
*/

void GameController::runGameLoop(Game game) {
    Board& board = game.getBoard();
    GameState state = GameState::PLAYING;
    ui.clearScreen();
    ui.displayBoard(board);
    while (state == GameState::PLAYING) { 
        state = game.run();
        ui.clearScreen();
        ui.displayBoard(board);
        std::string& message = game.getMessage();
        if (!message.empty()) {
            ui.print(message);
            message.clear();
        }
    }
    switch (state)
    {
    case GameState::BLACK_WIN:
        std::cout << "黑棋赢了!" <<std::endl;
        break;
    case GameState::WHITE_WIN:
        std::cout << "白棋赢了!" <<std::endl;
        break;
    default:
        break;
    }
}

GameConfig GameController::createDefaultConfig() {
    return GameConfig();
}

/* ============================================ */
/* 文件: GameController.h */
/* ============================================ */

#pragma once

#include "ConsoleUI.h"
#include "InputDevice.h"
#include "Game.h"

enum class GameControllerState
{
    START_GAME,
    MAIN_MENU
};

class GameController
{
private:
    GameControllerState state;
    ConsoleUI& ui;
    InputDevice& input;

    GameConfig createDefaultConfig();

public:
    GameController(ConsoleUI& ui, InputDevice& input);
    ~GameController() = default;
    GameConfig getGameConfig();
    Game initGame(GameConfig config);
    void runGameLoop(Game game);
};

/* ============================================ */
/* 文件: GameTypes.h */
/* ============================================ */

#pragma once

enum class PieceType {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

enum class GameResult
{
    NO_WINNER, //还没有分出胜负
    BLACK_WIN,
    WHITE_WIN,
    DRAW //平局
};

/* ============================================ */
/* 文件: HumanPlayer.cpp */
/* ============================================ */

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(InputDevice& input) : input(input) {}

PlayerAction HumanPlayer::getAction(Board& board, PieceType type) {
    InputResult result = input.getInput();
    PlayerAction action;
    switch (result.command)
    {
    case InputCommand::PLACE_PIECE:
        return {ActionType::PLACE_PIECE, result.pos};
    case InputCommand::QUIT:
        return {ActionType::QUIT};
    default:
        return {ActionType::INVALID};
    }
}

/* ============================================ */
/* 文件: HumanPlayer.h */
/* ============================================ */

#pragma once

#include "Player.h"

class HumanPlayer : public Player
{
private:
    InputDevice& input;

public:
    HumanPlayer(InputDevice& input);
    ~HumanPlayer() = default;
    PlayerAction getAction(Board& board, PieceType type) override;
};

/* ============================================ */
/* 文件: InputDevice.h */
/* ============================================ */

#pragma once

#include "Pos.h"

/**
 * 所有可能的输入命令
 */
enum class InputCommand {
    SELECT_FROM_MENU,
    PLACE_PIECE,
    QUIT,
    INVALID
};

/**
 * 具体输入的结果
 */
struct InputResult
{
    InputCommand command;
    Pos pos;
    int order;
};


/**
 * 这个类是所有输入的抽象，游戏对象从InputDevice实例中获取输入信息，而不必关心输入的来源和方式
 */
class InputDevice
{   
public:
    virtual ~InputDevice() = default;
    virtual InputResult getMenuInput() = 0;
    virtual InputResult getInput() = 0;
    virtual std::string getInput(const std::string& str) = 0;
};

/* ============================================ */
/* 文件: Judge.cpp */
/* ============================================ */

#include "Judge.h"

#include "Board.h"

bool Judge::isValidMove(const Board& board, const Pos pos) {
    if (Board::isOnBoard(pos) && board.getPos(pos) == PieceType::EMPTY) {
        return true;
    }
    return false;
}

GameResult Judge::ckeckWin(const Board& board, Pos lastDrop) {
    if (board.getLongestLine(lastDrop).length >= 5) {
        return (board.getPos(lastDrop) == PieceType::BLACK) ? GameResult::BLACK_WIN : GameResult::WHITE_WIN;
    }
    return GameResult::NO_WINNER;
}

/* ============================================ */
/* 文件: Judge.h */
/* ============================================ */

#pragma once

#include "Pos.h"
#include "Board.h"

class Judge
{
private:
    
public:
    Judge() = default;
    /* 判断在给定Pos处落子是否符合规则，如果符合，返回true */
    static bool isValidMove(const Board& board, const Pos pos);
    /**
     * @brief 根据上一个落子的位置检查当前棋局是否已经分出胜负
     * @return  NO_WINNER说明还未分出胜负
     */
    static GameResult ckeckWin(const Board& board, Pos lastDrop);
};

/* ============================================ */
/* 文件: Object.h */
/* ============================================ */

#pragma once

#include <string>
#include <cstdint>

class Object
{
private:
    /* data */
public:
    virtual ~Object() = default;
    virtual std::string toString() const {
        return "Object@" + std::to_string(reinterpret_cast<std::uintptr_t>(this));
    };
};

/* ============================================ */
/* 文件: Player.cpp */
/* ============================================ */

#include "Player.h"

#include <string>

Player::Player(std::string name) : name(name) {}

std::string Player::getName() const {
    return name;
}

Pos Player::calculateMove(Board& board, PieceType aiPiece) {
    return ai.calculateMove(board, aiPiece);
}

/* ============================================ */
/* 文件: Player.h */
/* ============================================ */

#pragma once

#include "InputDevice.h"
#include "AI.h"

enum class ActionType
{
    PLACE_PIECE,
    QUIT,
    INVALID
};

struct PlayerAction
{
    ActionType type;
    Pos pos;
};

class Player
{
public:
    Player() = default;
    virtual ~Player() =default;
    Player(std::string name);
    std::string getName() const;
    virtual PlayerAction getAction(Board& board, PieceType type) = 0;
    Pos calculateMove(Board& board, PieceType aiPiece);

private:
    std::string name;
    bool isAI;
    AI ai;
};

/* ============================================ */
/* 文件: Pos.cpp */
/* ============================================ */

#include <stdexcept>

#include "Pos.h"

Pos::Pos(int x, int y) : x(x), y(y) {}

Pos Pos::operator+(const Pos& other) const {
    return Pos(x + other.x, y + other.y);
}

Pos Pos::operator-(const Pos& other) const {
    return Pos(x - other.x, y - other.y);
}

Pos Pos::operator*(const int scalar) const {
    return Pos(x * scalar, y * scalar);
}

Pos& Pos::operator+=(const Pos& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Pos& Pos::operator-=(const Pos& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Pos& Pos::operator*=(const int scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Pos Pos::toPos(const Dir dir) {
    switch (dir)
    {
    case Dir::HORIZONTAL:
        return Pos(1, 0);
    case Dir::VERTICAL:
        return Pos(0, 1);
    case Dir::LEFT:
        return Pos(-1, 0);
    case Dir::RIGHT:
        return Pos(1, 0);
    case Dir::UP:
        return Pos(0, -1);
    case Dir::DOWN:
        return Pos(0, 1);
    case Dir::LEFTUP:
        return Pos(-1, -1);
    case Dir::LEFTDOWN:
        return Pos(-1, 1);
    case Dir::RIGHTUP:
        return Pos(1, -1);
    case Dir::RIGHTDOWN:
        return Pos(1, 1);
    default:
        throw std::invalid_argument("Invalid direction");
    }
}

Pos& Pos::to(const Dir dir) {
    *this += toPos(dir);
    return *this;
}

std::string Pos::toString() const {
    std::string str = "";
    return str += "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

/* ============================================ */
/* 文件: Pos.h */
/* ============================================ */

#pragma once

#include "Object.h"

/**
 * 这个枚举类表示棋盘上的八种方向
 */
enum class Dir
{
    HORIZONTAL,
    VERTICAL,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    LEFTUP,
    LEFTDOWN,
    RIGHTUP,
    RIGHTDOWN
};

/**
 * 这个类代表棋盘坐标，以棋盘左上角坐标为(0, 0)
 */
class Pos : public Object
{
public:
    /* 将给定方位转化成位移坐标 */
    static Pos toPos(const Dir dir);
    int x;
    int y;
    Pos() = default;
    Pos(int x, int y);
    Pos operator+(const Pos& other) const;
    Pos operator-(const Pos& other) const;
    Pos operator*(const int scalar) const;
    Pos& operator+=(const Pos& other);
    Pos& operator-=(const Pos& other);
    Pos& operator*=(const int scalar);
    /* 将给定坐标向给定方向移动一个单位 */
    Pos& to(const Dir dir);
    std::string toString() const override;
};

/* ============================================ */
/* 文件: ScoreMap.cpp */
/* ============================================ */

#include "ScoreMap.h"

#include <cmath>
#include <sstream>
#include <iomanip>

ScoreMap ScoreMap::createEmptyScoreMap() {
    ScoreMap emptyMap;
    for (auto& row : emptyMap.scoreMap) {
        for (auto& score : row) {
            score = 0;
        }
    }
    return emptyMap;
}

void ScoreMap::initScoreMap() {
    const int boardSize = scoreMap.size();
    const int center = boardSize / 2;

    float sigma = boardSize / 3; //标准差，控制衰减速度
    float amplitude = 100.0; //中心峰值，即最大分数

    for (int x = 0; x < boardSize; x++) {
        for (int y = 0; y < boardSize; y++) {
            float dx = x - center;
            float dy = y - center;
            float squareDist = dx * dx + dy * dy;

            float score = amplitude * exp(-squareDist / (2.0 * sigma * sigma));
            setScore(Pos(x, y), static_cast<int>(score));
        }
    }
}

Pos ScoreMap::findMax() {
    Pos maxPos = Pos(0, 0);
    int max = getScore(maxPos);
    for (int i = 0; i < scoreMap.size(); i++) {
        for (int j = 0; j < scoreMap.size(); j++) {
            int score = getScore(Pos(i, j));
            if (score > max) {
                maxPos = Pos(i, j);
                max = score;
            }
        }
    }
    return maxPos;
}

std::string ScoreMap::toString() const {
    std::stringstream ss;
    for (int i = 0; i < scoreMap.size(); i++) {
        ss << std::setw(2) << scoreMap.size() - i;
        for (int j = 0; j < scoreMap.size(); j++) {
            ss << std::setw(3) << getScore(Pos(i, j));
        }
        ss << std::endl;
    }
    ss << "   ";
    for (int i = 0; i < scoreMap.size(); i++) {
        ss << " " << char('A' + i) << " ";
    }
    return ss.str();
}

/* ============================================ */
/* 文件: ScoreMap.h */
/* ============================================ */

#pragma once

#include "Object.h"

#include <array>
#include "Pos.h"
#include "Board.h"

class ScoreMap : public Object
{
public:
    int getScore(Pos pos) const {return scoreMap[pos.x][pos.y];}
    void setScore(Pos pos, int score) {scoreMap[pos.x][pos.y] = score;}
    static ScoreMap createEmptyScoreMap();
    /**
     * @brief 根据距离棋盘中心的距离初始化分数图，呈正态分布
     */
    void initScoreMap();
    Pos findMax();

    std::string toString() const override;

private:
    /* AI对棋盘空位置的计算分数图 */
    std::array<std::array<int, Board::BOARD_SIZE>, Board::BOARD_SIZE> scoreMap;
};

/* ============================================ */
/* 文件: main.cpp */
/* ============================================ */

#include <iostream>
#include "GameController.h"
#include "ConsoleInput.h"

// ======测试时使用======
#include "..\test\Test.h"
using namespace Test;
// ======测试时使用======

int main() {
    // ======测试用例======
    AITest::testScoreMap();
    // ======测试用例======

    // ======主程序======
    //
    ConsoleUI ui;
    ConsoleInput input;
    GameController gameController(ui, input);
    gameController.runGameLoop(gameController.initGame(gameController.getGameConfig()));
    //
   // ======主程序======
   
    return 0;
}
