#pragma once

#include "core/Pos.h"

/**
 * 所有可能的输入命令
 */
enum class InputCommand {
    SELECT_FROM_MENU,
    PLACE_PIECE,
    QUIT,
    INVALID,
    NONE
};

/**
 * 具体输入的结果
 */
class InputResult
{
public:
    InputCommand command;
    Pos pos;
    int order;
    InputResult() : command(InputCommand::NONE) {}
};


/**
 * 这个类是所有输入的抽象，游戏对象从InputDevice实例中获取输入信息，而不必关心输入的来源和方式
 */
class InputDevice
{   
public:
    virtual ~InputDevice() = default;
    virtual bool hasInput() = 0;
    virtual char getInput() = 0;
    virtual std::string getInput(const std::string& str) = 0;
};