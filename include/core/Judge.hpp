#pragma once

#include "Pos.hpp"
#include "Board.hpp"

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
