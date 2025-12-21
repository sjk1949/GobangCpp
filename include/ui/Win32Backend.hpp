#pragma once
#include "ui/IConsoleBackend.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

class Win32Backend : public IConsoleBackend
{
public:
    Win32Backend();
    ~Win32Backend();

    void clear() override;
    void draw(const std::string& frame) override;
    void present() override;

    int width() const override;
    int height() const override;

private:
#ifdef _WIN32
    void checkResize();
    void recreateBackBuffer();

    HANDLE hFront = INVALID_HANDLE_VALUE;
    HANDLE hBack  = INVALID_HANDLE_VALUE;

    COORD visibleSize{};

    SHORT lastW = 0;
    SHORT lastH = 0;

    std::string buffer;
#endif
};
