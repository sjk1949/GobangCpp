#pragma once

#include "Player.h"

class HumanPlayer : public Player
{
private:
    InputDevice& input;

public:
    HumanPlayer(InputDevice& input);
    ~HumanPlayer() = default;
    //PlayerAction getAction(Board& board, PieceType type) override;
};