#pragma once

#include "command/Command.hpp"
#include "core/Pos.hpp"

class Game;

class GameCommand : public Command
{
public:
    virtual void execute(Game& game) = 0;
    virtual void undo(Game &game) {};
};

class PlacePieceCommand : public GameCommand
{
public:
    PlacePieceCommand(Pos pos) : pos(pos) {};
    void execute(Game& game) override;
private:
    Pos pos;
};

class UndoCommand : public GameCommand
{
public:
    void execute(Game& game) override;
};

class QuitGameCommand : public GameCommand
{
public:
    void execute(Game& game) override;
};

class HelpCommand : public GameCommand
{
public:
    void execute(Game& game) override;
};

class InvalidGameCommand : public GameCommand
{
public:
    void execute(Game& game) override;
};