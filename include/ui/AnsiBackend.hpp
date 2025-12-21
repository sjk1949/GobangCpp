#pragma once
#include "ui/ConsoleBackend.hpp"
#include <string>
#include <vector>

class AnsiBackend : public ConsoleBackend {
public:
    AnsiBackend();

    void beginFrame() override;
    void draw(const std::string& utf8Text) override;
    void endFrame() override;
    void onResize() override;

private:
    std::string buffer;
    int lastLineCount = 0;

    static std::vector<std::string> splitLines(const std::string& s);
};
