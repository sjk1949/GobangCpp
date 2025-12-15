#pragma once

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
    /* 输出信息 */
    static void print(const std::string& str);

private:
};