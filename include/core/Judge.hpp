#pragma once

#include "Pos.hpp"
#include "Board.hpp"
#include "core/ChessPattern.hpp"

/**
 * 禁手包括三三，三四，长连禁手
 */
enum class ForbiddenType
{
    NONE, // 无禁手
    OVERLINE, // 长连禁手：当黑棋走一步棋，形成长连棋型，则此点为“禁手”
    DOUBLE_FOUR, // 当黑棋走一步棋，同时形成两个或两个以上的“四”且没有形成“五连”时，那一步棋就是黑棋禁手。
    DOUBLE_THREE // 当黑棋走一步棋，同时形成两个或两个以上的“活三”且没有形成“五连”时，那一步棋就是黑棋禁手。
};

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
    /**
     * @brief 检测黑棋下在给定的位置会不会形成禁手
     * @return 返回禁手类型，如果没有禁手，返回ForbiddenType::NONE
     */
    static ForbiddenType checkForbidden(const Board& board, Pos pos);
private:
    /**
     * @brief 根据给定的棋型，检查所属的类型
     */
    static ChessPatternType checkChessPatternType(ChessPattern pattern);
};
