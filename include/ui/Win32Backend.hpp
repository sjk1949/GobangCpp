#pragma once
#ifdef _WIN32

#include "ui/ConsoleBackend.hpp"
#include <windows.h>
#include <vector>
#include <string>

class Win32Backend : public ConsoleBackend {
public:
    Win32Backend();
    ~Win32Backend();

    void beginFrame() override;
    void draw(const std::string& utf8Text) override;
    void endFrame() override;
    void onResize() override;

private:
    HANDLE hOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    int width = 0;
    int height = 0;

    std::vector<CHAR_INFO> buffer;

    int cursorX = 0;
    int cursorY = 0;

    void resizeBuffer();
    static std::wstring utf8ToUtf16(const std::string& s);
};

#endif
