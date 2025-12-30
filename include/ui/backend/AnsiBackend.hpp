/**
 * @file AnsiBackend.hpp
 * @brief Console rendering backend using ANSI escape sequences.
 *
 * This class is responsible for rendering text-based UI frames using
 * ANSI escape codes. It minimizes flickering by:
 *  - Using an off-screen string buffer per frame
 *  - Tracking previous frame line lengths
 *  - Clearing terminal lines only when necessary
 *
 * Design trade-offs and terminal compatibility issues (CMD, PowerShell,
 * Git Bash) were analyzed with external technical assistance and finalized
 * by the author.
 */

#pragma once
#include "ui/backend/ConsoleBackend.hpp"
#include <string>
#include <vector>

class AnsiBackend : public ConsoleBackend {
public:
    AnsiBackend();
    ~AnsiBackend();

    void beginFrame() override;
    void draw(const std::string& utf8Text) override;
    void endFrame() override;
    void onResize() override;

private:
    std::string buffer;
    int lastLineCount = 0;
    std::vector<std::string> lastLines;

    static std::vector<std::string> splitLines(const std::string& s);
};
