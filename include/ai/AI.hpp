#pragma once

#include "core/Board.hpp"
#include "utils/ScoreMap.hpp"

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
    /**
     * @brief 事实上，当AI下棋的时候，它不需要每次都更新所有的ScoreMap，而只需要更新新落子附近的即可
     * @todo
     */
    void updateScoreMap(ScoreMap& scoreMap);
    static int scorePattern(const PatternType pattern);
    static int getPosScore(Board& board, Pos pos, PieceType aiPiece);
};