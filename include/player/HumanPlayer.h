#pragma once

#include "Player.h"

class HumanPlayer : public Player
{
private:

public:
    HumanPlayer() = default;
    ~HumanPlayer() = default;
    std::unique_ptr<GameCommand> getCommand(Board& board, PieceType type) override;
};