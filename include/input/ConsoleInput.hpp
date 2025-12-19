#pragma once

#include "InputDevice.hpp"
#include "NonBlockingInput.hpp"

class ConsoleInput : public InputDevice
{
public:
    ConsoleInput() = default;
    ///~ConsoleInput() override = default;
    bool hasInput() override;
    char getInput() override;
    std::string getInput(const std::string& str) override;

private:
    NonBlockingInput nbi;
};