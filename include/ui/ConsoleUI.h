#pragma once

#include "core/Game.h"
#include "core/Board.h"
#include "core/GameConfig.h"

class ConsoleUI
{
public:
    /* 清屏 */
    static void clearScreen();
    /* 展示开始菜单 */
    static void displayStartMenu(GameConfig config);
    /* 展示给定的棋盘 */
    static void displayBoard(Board& board);
    /* 展示游戏 */
    static void displayGame(Game& game);
    /* 输出信息 */
    static void print(const std::string& str);

private:
};