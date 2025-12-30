#pragma once

#include "Player.hpp"

class AIPlayer : public Player
{
public:
    AIPlayer(std::string name, AIStrategy strategy);
    std::unique_ptr<GameCommand> getCommand(Board& board, PieceType type) override;
};