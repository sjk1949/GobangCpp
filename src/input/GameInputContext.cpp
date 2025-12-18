#include "input/GameInputContext.h"

#include <iostream>

void GameInputContext::onInput(const char& c) {
    std::cerr << "[DEBUG] PRESSED: " << int(c) << std::endl;
    if (c == 13) {
        result = parseInput(buffer);
        buffer = "";
    } else if (c == 8) {
        if (!buffer.empty()) {
            buffer.pop_back();
        }
    } else {
        buffer.push_back(c);
    }
}

std::string GameInputContext::getBuffer() {
    return buffer;
}