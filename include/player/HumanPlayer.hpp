#pragma once

#include "Player.hpp"

class HumanPlayer : public Player
{
private:

public:
    HumanPlayer(std::string name, AIStrategy strategy);
    std::unique_ptr<GameCommand> getCommand(Board& board, PieceType type) override;
};