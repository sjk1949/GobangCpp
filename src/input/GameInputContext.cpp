#include "input/GameInputContext.h"

#include <utils/Logger.h>

void GameInputContext::onInput(const char& c) {
    Logger::debug("PRESSED: ", int(c));
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