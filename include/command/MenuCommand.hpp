#pragma once

#include "command/Command.hpp"

class Menu;

class MenuCommand : public Command
{
public:
    virtual void execute(Menu& menu) = 0;
};

class MoveUpCommand : public MenuCommand
{
public:
    void execute(Menu& menu) override;
};

class MoveDownCommand : public MenuCommand
{
public:
    void execute(Menu& menu) override;
};

class ConfirmCommand : public MenuCommand
{
public:
    void execute(Menu& menu) override;
};

class AdjustCommand : public MenuCommand
{
public:
    AdjustCommand(int dir) : dir(dir) {};
    void execute(Menu& menu) override;
private:
    int dir;
};