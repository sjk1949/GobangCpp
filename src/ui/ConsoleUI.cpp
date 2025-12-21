#include "ui/ConsoleUI.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif
#include "core/Game.hpp"
#include "core/Pos.hpp"
#include "menu/Menu.hpp"
#include "utils/Logger.hpp"

ConsoleUI::ConsoleUI() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    std::cout << "\033[?25l"; // 将光标设置为隐藏模式
    // @todo 先把清屏语句加上，这样至少暂时会好看一些
    std::cout << "\033[2J\033[H";
}

void ConsoleUI::clear() {
    // ANSI 转义码：\033[2J 清屏，\033[H 光标移到左上角, 已废弃
    //std::cout << "\033[2J\033[H";
    buffer.str("");
}

void ConsoleUI::displayMenu(Menu& menu) {
    print(menu.toString(), "\n");
    print("\'w\'\'s\'键上下滚动，\'a\'\'d\'键修改值\n");
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
    if (game.hasTimeLimit()) {
        print("              Time Left: ", game.getRemainingTime(), "s");
    }
    print("\n");
    print(game.getMessage(), "\n");
    if (game.getGameState() != GameState::PLAYING) {
        displayGameResult(game.getGameState());
        print("按[ENTER]键回到菜单\n");
    }
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