#include "ui/ConsoleUI.h"

#include <iostream>
#include <sstream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif
#include "core/Game.h"
#include "core/Pos.h"
#include "utils/Logger.h"

ConsoleUI::ConsoleUI() {
    std::cout << "\033[?25l"; // 将光标设置为隐藏模式
    // @todo 先把清屏语句加上，这样至少暂时会好看一些
    std::cout << "\033[2J\033[H";
}

void ConsoleUI::clear() {
    // ANSI 转义码：\033[2J 清屏，\033[H 光标移到左上角, 已废弃
    //std::cout << "\033[2J\033[H";
    buffer.str("");
}

void ConsoleUI::displayStartMenu(const GameConfig config) {
    buffer << "======================================" << std::endl;
    buffer << "=             五子棋小游戏            =" << std::endl;
    buffer << "=               @copyright 韩书钰     =" << std::endl;
    buffer << "======================================" << std::endl;
    buffer << "==============开始菜单================" << std::endl;
    buffer << "1.开始游戏" << std::endl;
    buffer << "2.玩家设置                AI" << std::endl;
    buffer << "      Player1            " << config.player1IsAI << std::endl;
    buffer << "      Player2            " << std::endl;
    buffer << "3.退出游戏" << std::endl;
}

void ConsoleUI::displayBoard(const Board& board) {
    print(board.toString(), "\n");
}

void ConsoleUI::displayGame(Game& game) {
    displayBoard(game.getBoard());
    print("Current Player: ");
    if (game.getCurrentPieceType() == PieceType::BLACK) {
        print("BLACK ●");
    } else {
        print("WHITE ○");
    }
    print("              Time Left: ", game.getRemainingTime(), "s\n");
    print(game.getMessage(), "\n");
}

void ConsoleUI::displayGameResult(const GameState& state) {
    switch (state)
    {
    case GameState::BLACK_WIN:
        print("黑棋赢了!\n");
        break;
    case GameState::WHITE_WIN:
        print("白棋赢了!\n");
        break;
    case GameState::DRAW:
        print("平局\n");
        break;
    default:
        break;
    }
}

void ConsoleUI::print(const std::string& str) {
    buffer << str;
}

void ConsoleUI::drawDebugPanel() {
    print("[DEBUG LOG]\n");
    for (auto log : Logger::getRecentLogs(2)) {
        print(log, "\n");
    }
}

void ConsoleUI::flip() {
    if (saveHistoryDraw == false) {
        std::cout << "\033[H";
        std::cout << "\033[J";
    }
    std::cout << buffer.str();
    std::cout.flush();
    ;
}