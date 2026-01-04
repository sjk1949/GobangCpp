#pragma once

#include <memory>
#include "command/GameCommand.hpp"
#include "ai/AI.hpp"

class Player
{
public:
    bool isAI;

    //Player() = default;
    virtual ~Player() =default;
    Player(std::string name, AIStrategy strategy);
    std::string getName() const;
    void push(std::unique_ptr<GameCommand> command);
    virtual std::unique_ptr<GameCommand> getCommand(Board& board, PieceType type) = 0;

protected:
    std::string name;
    AI ai;
    std::unique_ptr<GameCommand> commandBuffer;
    
    //Pos calculateMove(Board& board, PieceType aiPiece);
};