#pragma once

#include "Player.hpp"

class AIPlayer : public Player
{
public:
    std::unique_ptr<GameCommand> getCommand(Board& board, PieceType type) override;
};