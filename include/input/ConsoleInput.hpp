#pragma once

#include "InputDevice.hpp"
#include "NonBlockingInput.hpp"

class ConsoleInput : public InputDevice
{
public:
    ConsoleInput() = default;
    bool hasInput() override;
    char getInput() override;

private:
    NonBlockingInput nbi;
};