#include "ui/ConsoleUI.h"

#include <iostream>
#include <sstream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif
#include "core/Game.h"
#include "core/Pos.h"

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
    buffer << board.toString() << std::endl;
}

void ConsoleUI::displayGame(Game& game) {
    displayBoard(game.getBoard());
    std::string& message = game.getMessage();
    if (!message.empty()) {
        print(message);
        message.clear();
    }
}

void ConsoleUI::displayGameResult(const GameState& state) {
    switch (state)
    {
    case GameState::BLACK_WIN:
        buffer << "黑棋赢了!" << std::endl;
        break;
    case GameState::WHITE_WIN:
        buffer << "白棋赢了!" << std::endl;
        break;
    case GameState::DRAW:
        buffer << "平局！" << std::endl;
        break;
    default:
        break;
    }
}

void ConsoleUI::print(const std::string& str) {
    buffer << str << std::endl;
}

void ConsoleUI::print(const int& num) {
    buffer << num << std::endl;
}

void ConsoleUI::flip() {
    std::cout << "\033[H";
    std::cout << buffer.str() << std::endl;
}