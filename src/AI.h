#pragma once

#include "Board.h"
#include "ScoreMap.h"

class AI
{
public:
    AI();
    /**
     * @brief 给出下一步棋的位置
     * @param aiPiece   调用方的持子类型，从BLACK, WHITE中选择
     */
    Pos calculateMove(Board& board, PieceType aiPiece);

private:
    /**
     * @brief 一个完全随机的下棋函数，当场上棋子较多时可能比较费时
     * @see 引自DeepSeek
     */
    Pos randomMove(Board& board);
    /**
     * @brief 根据分数图选取分数最大的位置落子
     */
    Pos maxScoreMove(Board& board, PieceType aiPiece);
    /**
     * @brief 根据给定棋盘和持子方生成分数图
     */
    ScoreMap genScoreMap(Board& board, PieceType aiPiece);
    void updateScoreMap(ScoreMap& scoreMap);
};