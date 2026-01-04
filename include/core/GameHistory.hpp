#pragma once

#include <vector>
#include "core/GameConfig.hpp"
#include "command/GameCommand.hpp"

struct Move {
    Pos pos;
    PieceType type;
};

class GameHistory
{
private:
    std::vector<Move> moveList;

public:
    void addMove(Move move);
    /**
     * @return 如果操作记录为空，返回false
     */
    bool canUndo();
    /**
     * @brief 撤销上一步操作，并返回Move
     */
    Move undoLastMove();
};