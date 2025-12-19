#pragma once

#include "InputContext.hpp"

#include <string>

class MenuInputContext : public InputContext
{
public:
    void onInput(const char& c) override;
    std::string getBuffer() override {return std::string("");};
};
