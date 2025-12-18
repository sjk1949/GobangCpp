#pragma once

#include "input/InputDevice.h"
#include "ai/AI.h"

enum class ActionType
{
    PLACE_PIECE,
    QUIT,
    INVALID
};

struct PlayerAction
{
    ActionType type;
    Pos pos;
};

class Player
{
public:
    Player() = default;
    virtual ~Player() =default;
    Player(std::string name);
    std::string getName() const;
    //virtual PlayerAction getAction(Board& board, PieceType type) = 0;
    Pos calculateMove(Board& board, PieceType aiPiece);

private:
    std::string name;
    bool isAI;
    AI ai;
};