#pragma once

#include <memory>
#include "command/Command.hpp"

class InputContext
{
public:
    InputContext();
    virtual ~InputContext() = default;
    virtual void onInput(const char& c) = 0;
    std::unique_ptr<Command> popCommand();
    virtual std::string getBuffer() = 0;

protected:
    std::unique_ptr<Command> commandBuffer;
    /* 解析字符串输入 */
    std::unique_ptr<Command> parseMenuInput(const std::string& input);
};