#pragma once
#include <string>

class ConsoleBackend {
public:
    virtual ~ConsoleBackend() = default;

    virtual void beginFrame() = 0;
    virtual void draw(const std::string& utf8Text) = 0;
    virtual void endFrame() = 0;

    virtual void onResize() = 0;
};
