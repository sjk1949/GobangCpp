#include "ui/ConsoleUI.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#include "ui/Win32Backend.hpp"
#endif
#include "ui/AnsiBackend.hpp"
#include "core/Game.hpp"
#include "core/Pos.hpp"
#include "menu/Menu.hpp"
#include "utils/Logger.hpp"

ConsoleUI::ConsoleUI() {
    detectBackend();
}

void ConsoleUI::detectBackend() {
#ifdef _WIN32
    // Git Bash / MSYS 会设置这些
    if (std::getenv("MSYSTEM") || std::getenv("TERM")) {
        backend = std::make_unique<AnsiBackend>();
    } else {
        backend = std::make_unique<Win32Backend>();
    }
#else
    backend = std::make_unique<AnsiBackend>();
#endif
}

void ConsoleUI::clear() {
    buffer.str("");
    buffer.clear();
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
    backend->beginFrame();
    backend->draw(buffer.str());
    backend->endFrame();
}