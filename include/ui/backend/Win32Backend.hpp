/**
 * @file Win32Backend.hpp
 * @brief Win32 console backend implementation for text-based UI rendering.
 *
 * This backend provides a Windows-specific implementation of the
 * ConsoleBackend interface using Win32 Console APIs. It supports:
 *  - Flicker-free rendering via off-screen buffers
 *  - Accurate cursor positioning using absolute coordinates
 *  - Proper handling of console resize events
 *
 * The overall architecture and several low-level implementation details
 * were developed with the assistance of AI-based debugging and design tools
 * (e.g., ChatGPT), and were subsequently integrated, refined, and verified
 * by the author.
 */

#pragma once
#ifdef _WIN32

#include "ui/backend/ConsoleBackend.hpp"
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
