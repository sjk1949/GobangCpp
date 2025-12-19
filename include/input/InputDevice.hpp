#pragma once

#include "core/Pos.hpp"

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