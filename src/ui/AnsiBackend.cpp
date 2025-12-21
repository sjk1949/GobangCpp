#include "ui/AnsiBackend.hpp"
#include <iostream>

AnsiBackend::AnsiBackend()
{
    std::cout << "\033[?25l";        // hide cursor
    std::cout << "\033[2J\033[H";    // clear screen
}

void AnsiBackend::clear()
{
    buffer.clear();
}

void AnsiBackend::draw(const std::string& frame)
{
    buffer = frame;
}

void AnsiBackend::present()
{
    // 回到左上角 + 清屏，保证完全覆盖旧帧
    std::cout << "\033[H\033[2J";
    std::cout << buffer;
    std::cout.flush();
}

int AnsiBackend::width() const
{
    return 120; // ANSI 下不可靠，仅作为逻辑参考
}

int AnsiBackend::height() const
{
    return 40;
}
