#pragma once

#include <sstream>
#include <utility>
#include "core/Game.h"
#include "core/Board.h"
#include "core/GameConfig.h"

class ConsoleUI
{
public:
    ConsoleUI();
    /* 清屏 */
    void clear();
    /* 展示开始菜单 */
    void displayStartMenu(const GameConfig config);
    /* 展示给定的棋盘 */
    void displayBoard(const Board& board);
    /* 展示游戏 */
    void displayGame(Game& game);
    /* 展示游戏结果 */
    void displayGameResult(const GameState& state);
    /* 输出信息 */
    void print(const std::string& str);

    template<typename... Args>
    void print(Args&&... args) {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        print(static_cast<const std::string&>(oss.str()));
    }

    /* 输出调试信息 */
    void drawDebugPanel();
    /**
     * @brief 将缓冲区的内容输出到屏幕上
     */
    void flip();

private:
    bool saveHistoryDraw = false; // 是否保存之前所有的绘制不清屏
    std::stringstream buffer; // 缓冲区
};