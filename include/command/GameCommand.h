#pragma once

#include "Game.h"

class GameCommand
{
public:
    virtual ~GameCommand() = default;
    virtual void execute(Game& game) = 0;
};

class NoneGameCommand : public GameCommand
{
public:
    void execute(Game& game) override;
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