#pragma once

#include "Player.h"

class AIPlayer : public Player
{
public:
    InputResult getCommand(Board& board, PieceType type) override;
};