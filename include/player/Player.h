#pragma once

#include "input/InputDevice.h"
#include "ai/AI.h"

class Player
{
public:
    Player() = default;
    virtual ~Player() =default;
    Player(std::string name);
    std::string getName() const;
    void push(InputResult result);
    bool hasCommand();
    virtual InputResult getCommand(Board& board, PieceType type) = 0;

protected:
    std::string name;
    bool isAI;
    AI ai;
    InputResult result;
    
    Pos calculateMove(Board& board, PieceType aiPiece);
};