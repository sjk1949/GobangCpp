#pragma once

#include "Player.h"

class HumanPlayer : public Player
{
private:

public:
    HumanPlayer() = default;
    ~HumanPlayer() = default;
    InputResult getCommand(Board& board, PieceType type) override;
};