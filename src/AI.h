#pragma once

#include "Board.h"
#include "ScoreMap.h"

class AI
{
public:
    /**
     * @brief 给出下一步棋的位置
     * @param aiPiece   调用方的持子类型，从BLACK, WHITE中选择
     */
    Pos calculateMove(Board& board, PieceType aiPiece);

private:
    ScoreMap scoreMap;
    /**
     * @brief 一个完全随机的下棋函数，当场上棋子较多时可能比较费时
     * @see 引自DeepSeek
     */
    Pos randomMove(Board&board);
};