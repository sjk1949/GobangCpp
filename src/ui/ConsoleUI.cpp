#include "ui/ConsoleUI.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#include "ui/backend/Win32Backend.hpp"
#endif
#include "ui/backend/AnsiBackend.hpp"
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

void ConsoleUI::displayBoard(const Board& board, std::vector<Pos> highlights) {
    for (int i = Board::BOARD_SIZE; i >= 1; i--) {
        print(std::setw(2), i);
        displayBoardRow(board, i, highlights);
        print("\n");
    }
    print("  ");
    for (int i = 0; i < Board::BOARD_SIZE; i++) {
        print(" ", char('A' + i), " ");
    }
}

void ConsoleUI::displayBoardRow(const Board& board, int row, std::vector<Pos> highlights) {
    static const int BLINK_INTERVAL = 200;// 闪动时间间隔，单位ms
    static bool blink = false; // 如果为真，需要闪烁的图形消失
    static int timeElapsed = 0;
    static auto lastChangeTime = std::chrono::steady_clock::now();

    // 更新是否在这一帧闪烁
    if (timeElapsed > BLINK_INTERVAL) {
        timeElapsed = 0;
        blink = !blink;
        lastChangeTime = std::chrono::steady_clock::now();
    } else {
        timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastChangeTime).count();
    }
    for (int i = 0; i < Board::BOARD_SIZE; i++) {
        Pos pos(i, Board::BOARD_SIZE - row);
        if (std::find(highlights.begin(), highlights.end(), pos) != highlights.end() && blink) {
            print("   ");
        } else {
            print(board.pieceToString(board.getPos(pos)));
        }
    }
}

void ConsoleUI::displayGame(Game& game) {
    displayBoard(game.getBoard(), game.getHighlights());
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