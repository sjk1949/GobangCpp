#pragma once
#include <string>

class IConsoleBackend
{
public:
    virtual ~IConsoleBackend() = default;

    virtual void clear() = 0;
    virtual void draw(const std::string& frame) = 0;
    virtual void present() = 0;

    virtual int width() const = 0;
    virtual int height() const = 0;
};
