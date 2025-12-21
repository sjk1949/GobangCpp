#include "ui/Win32Backend.hpp"

#ifdef _WIN32

Win32Backend::Win32Backend()
{
    hFront = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO info{};
    GetConsoleScreenBufferInfo(hFront, &info);

    // 使用“可见窗口尺寸”，不是 dwSize
    visibleSize.X = info.srWindow.Right  - info.srWindow.Left + 1;
    visibleSize.Y = info.srWindow.Bottom - info.srWindow.Top  + 1;

    lastW = visibleSize.X;
    lastH = visibleSize.Y;

    hBack = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        CONSOLE_TEXTMODE_BUFFER,
        nullptr
    );

    SetConsoleActiveScreenBuffer(hBack);
    SetConsoleCursorPosition(hBack, {0, 0});
}

Win32Backend::~Win32Backend()
{
    SetConsoleActiveScreenBuffer(hFront);
    CloseHandle(hBack);
}

void Win32Backend::clear()
{
    buffer.clear();
}

void Win32Backend::draw(const std::string& frame)
{
    buffer = frame;
}

void Win32Backend::checkResize()
{
    CONSOLE_SCREEN_BUFFER_INFO info{};
    GetConsoleScreenBufferInfo(hFront, &info);

    SHORT w = info.srWindow.Right  - info.srWindow.Left + 1;
    SHORT h = info.srWindow.Bottom - info.srWindow.Top  + 1;

    if (w != lastW || h != lastH) {
        lastW = w;
        lastH = h;
        visibleSize = { w, h };
        recreateBackBuffer();
    }
}

void Win32Backend::recreateBackBuffer()
{
    CloseHandle(hBack);

    hBack = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        CONSOLE_TEXTMODE_BUFFER,
        nullptr
    );

    SetConsoleActiveScreenBuffer(hBack);
    SetConsoleCursorPosition(hBack, {0, 0});
}

void Win32Backend::present()
{
    checkResize();

    std::string frame;
    frame.reserve(visibleSize.X * visibleSize.Y);

    int x = 0, y = 0;
    for (char c : buffer) {
        if (c == '\n') {
            while (x < visibleSize.X) {
                frame.push_back(' ');
                x++;
            }
            x = 0;
            if (++y >= visibleSize.Y) break;
        } else {
            frame.push_back(c);
            if (++x >= visibleSize.X) {
                x = 0;
                if (++y >= visibleSize.Y) break;
            }
        }
    }

    frame.resize(visibleSize.X * visibleSize.Y, ' ');

    DWORD written = 0;
    WriteConsoleOutputCharacterA(
        hBack,
        frame.c_str(),
        (DWORD)frame.size(),
        {0, 0},
        &written
    );

    SetConsoleActiveScreenBuffer(hBack);
}

int Win32Backend::width() const
{
    return visibleSize.X;
}

int Win32Backend::height() const
{
    return visibleSize.Y;
}

#endif
