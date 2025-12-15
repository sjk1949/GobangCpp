#pragma once

#include "core/Pos.h"

/**
 * 所有可能的输入命令
 */
enum class InputCommand {
    SELECT_FROM_MENU,
    PLACE_PIECE,
    QUIT,
    INVALID
};

/**
 * 具体输入的结果
 */
struct InputResult
{
    InputCommand command;
    Pos pos;
    int order;
};


/**
 * 这个类是所有输入的抽象，游戏对象从InputDevice实例中获取输入信息，而不必关心输入的来源和方式
 */
class InputDevice
{   
public:
    virtual ~InputDevice() = default;
    virtual InputResult getMenuInput() = 0;
    virtual InputResult getInput() = 0;
    virtual std::string getInput(const std::string& str) = 0;
};