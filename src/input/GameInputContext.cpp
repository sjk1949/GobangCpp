#include "input/GameInputContext.h"

#include <algorithm>
#include <regex>
#include "core/Board.h"
#include "command/GameCommand.h"
#include "utils/Logger.h"

void GameInputContext::onInput(const char& c) {
    Logger::debug("PRESSED: ", int(c));
    if (c == 13) {
        commandBuffer = parseInput(buffer);
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

std::unique_ptr<Command> GameInputContext::parseInput(const std::string& input) {
    Logger::debug("INPUT: ", input);
    int n;
    char c;

    if (input.empty()) {
        return std::make_unique<InvalidGameCommand>();
    }

    std::string lowerInput = toLower(input);
    if (lowerInput == "quit" || lowerInput == "q") {
        return std::make_unique<QuitGameCommand>();
    } else  if (parseStringRegex(lowerInput, c, n)) {
        return std::make_unique<PlacePieceCommand>(parsePos(c, n));
    } else {
        return std::make_unique<InvalidGameCommand>();
    }
}

Pos GameInputContext::parsePos(const char& c, const int& num) {
    Pos pos;
    pos.x = c - 'a';
    pos.y = Board::rowToPosY(num);
    return pos;
}

std::string GameInputContext::toLower(const std::string& str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });
    return lower;
}

bool GameInputContext::parseStringRegex(const std::string& str, char& c, int& num) {
    std::regex pattern1("^([a-zA-Z])(\\d+)$");
    std::regex pattern2("^(\\d+)([a-zA-Z])$");
    std::smatch matches;
    
    if (std::regex_match(str, matches, pattern1)) {
        c = matches[1].str()[0];  // 获取字符
        num = std::stoi(matches[2].str());  // 获取数字
        return true;
    } else if (std::regex_match(str, matches, pattern2)) {
        c = matches[2].str()[0];  // 获取字符
        num = std::stoi(matches[1].str());  // 获取数字
        return true;
    }
    return false;
}

bool GameInputContext::parseInt(const std::string& str, int& num) {
    std::regex pattern("^\\d+$");
    std::smatch matches;
    
    if (std::regex_match(str, matches, pattern)) {
        num = std::stoi(matches[1].str());  // 获取数字
        return true;
    }
    return false;
}