#include "ui/AnsiBackend.hpp"
#include <iostream>
#include <sstream>

AnsiBackend::AnsiBackend() {
    std::cout << "\033[?25l"; // hide cursor
}

void AnsiBackend::beginFrame() {
    buffer.clear();
}

void AnsiBackend::draw(const std::string& utf8Text) {
    buffer += utf8Text;
}

std::vector<std::string> AnsiBackend::splitLines(const std::string& s) {
    std::vector<std::string> lines;
    std::stringstream ss(s);
    std::string line;
    while (std::getline(ss, line)) {
        lines.push_back(line);
    }
    if (!s.empty() && s.back() == '\n') {
        lines.push_back("");
    }
    return lines;
}

void AnsiBackend::endFrame() {
    auto lines = splitLines(buffer);
    int currentLines = static_cast<int>(lines.size());

    // 回到左上角
    std::cout << "\033[H";

    // 逐行：清行 → 写行
    for (const auto& line : lines) {
        std::cout << "\033[K";   // 清除整行
        std::cout << line;
        std::cout << '\n';
    }

    // 如果新帧行数比旧帧少，清掉多余的旧行
    for (int i = currentLines; i < lastLineCount; ++i) {
        std::cout << "\033[K\n";
    }

    lastLineCount = currentLines;
    std::cout.flush();
}

void AnsiBackend::onResize() {
    lastLineCount = 0;
}
