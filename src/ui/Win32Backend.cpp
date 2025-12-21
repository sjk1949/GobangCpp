#ifdef _WIN32

#include "ui/Win32Backend.hpp"

#include <iostream>

Win32Backend::Win32Backend() {
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);

    std::wcout << L"\x1b[?25l"; // hide cursor
    resizeBuffer();
}

Win32Backend::~Win32Backend() {
    std::wcout << L"\x1b[?25h"; // show cursor
}

void Win32Backend::resizeBuffer() {
    GetConsoleScreenBufferInfo(hOut, &csbi);
    width  = csbi.srWindow.Right  - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top  + 1;

    buffer.resize(width * height);
}

void Win32Backend::beginFrame() {
    resizeBuffer();

    for (auto& c : buffer) {
        c.Char.UnicodeChar = L' ';
        c.Attributes = csbi.wAttributes;
    }

    cursorX = 0;
    cursorY = 0;
}

void Win32Backend::draw(const std::string& utf8Text) {
    std::wstring w = utf8ToUtf16(utf8Text);

    for (wchar_t ch : w) {
        if (ch == L'\n') {
            cursorX = 0;
            cursorY++;
            continue;
        }

        if (cursorX >= width || cursorY >= height)
            continue;

        buffer[cursorY * width + cursorX].Char.UnicodeChar = ch;
        cursorX++;
    }
}

void Win32Backend::endFrame() {
    SMALL_RECT rect{
        0, 0,
        static_cast<SHORT>(width - 1),
        static_cast<SHORT>(height - 1)
    };

    COORD bufSize{ (SHORT)width, (SHORT)height };
    COORD bufCoord{ 0, 0 };

    WriteConsoleOutputW(
        hOut,
        buffer.data(),
        bufSize,
        bufCoord,
        &rect
    );
}

void Win32Backend::onResize() {
    resizeBuffer();
}

std::wstring Win32Backend::utf8ToUtf16(const std::string& s) {
    if (s.empty()) return L"";
    int len = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, nullptr, 0);
    std::wstring ws(len - 1, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, ws.data(), len);
    return ws;
}

#endif
