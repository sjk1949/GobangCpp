#pragma once

#include "command/Command.h"
#include "core/Pos.h"

class Game;

class GameCommand : public Command
{
public:
    virtual void execute(Game& game) = 0;
};

class PlacePieceCommand : public GameCommand
{
public:
    PlacePieceCommand(Pos pos) : pos(pos) {};
    void execute(Game& game) override;
private:
    Pos pos;
};

class QuitGameCommand : public GameCommand
{
public:
    void execute(Game& game) override;
};

class InvalidGameCommand : public GameCommand
{
public:
    void execute(Game& game) override;
};