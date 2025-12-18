#pragma once

#include "InputContext.h"
#include <string>

class GameInputContext : public InputContext
{
private:
    std::string buffer;
public:
    void onInput(const char& c) override;
    std::string getBuffer() override;
};