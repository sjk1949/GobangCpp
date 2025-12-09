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