#pragma once
#include "ui/IConsoleBackend.hpp"
#include <string>

class AnsiBackend : public IConsoleBackend
{
public:
    AnsiBackend();

    void clear() override;
    void draw(const std::string& frame) override;
    void present() override;

    int width() const override;
    int height() const override;

private:
    std::string buffer;
};
