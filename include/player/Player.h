#pragma once

#include <memory>
#include "command/GameCommand.h"
#include "ai/AI.h"

class Player
{
public:
    Player() = default;
    virtual ~Player() =default;
    Player(std::string name);
    std::string getName() const;
    void push(std::unique_ptr<GameCommand> command);
    virtual std::unique_ptr<GameCommand> getCommand(Board& board, PieceType type) = 0;

protected:
    std::string name;
    bool isAI;
    AI ai;
    std::unique_ptr<GameCommand> commandBuffer;
    
    Pos calculateMove(Board& board, PieceType aiPiece);
};