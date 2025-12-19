#include "input/InputContext.h"

#include <algorithm>
#include <regex>
#include "core/Board.h"
#include "utils/Logger.h"

InputContext::InputContext() {}

bool InputContext::hasCommand() {
    return result.command != InputCommand::NONE;
}

InputResult InputContext::popCommand() {
    InputResult out = result;
    result.command = InputCommand::NONE;
    return out;
}

InputResult InputContext::parseInput(const std::string& input) {
    Logger::debug("INPUT: ", input);
    InputResult result;
    int n;
    char c;

    if (input.empty()) {
        result.command = InputCommand::INVALID;
        return result;
    }

    std::string lowerInput = toLower(input);
    if (lowerInput == "quit" || lowerInput == "q") {
        result.command = InputCommand::QUIT;
    } else  if (parseStringRegex(lowerInput, c, n)) {
        result.command = InputCommand::PLACE_PIECE;
        result.pos = parsePos(c, n);
    } else {
        result.command = InputCommand::INVALID;
    }

    return result;
}

Pos InputContext::parsePos(const char& c, const int& num) {
    Pos pos;
    pos.x = c - 'a';
    pos.y = Board::rowToPosY(num);
    return pos;
}

std::string InputContext::toLower(const std::string& str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });
    return lower;
}

bool InputContext::parseStringRegex(const std::string& str, char& c, int& num) {
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

bool InputContext::parseInt(const std::string& str, int& num) {
    std::regex pattern("^\\d+$");
    std::smatch matches;
    
    if (std::regex_match(str, matches, pattern)) {
        num = std::stoi(matches[1].str());  // 获取数字
        return true;
    }
    return false;
}

/*
InputResult InputContext::parseMenuInput(const std::string& input) {
    InputResult result;
    int n;

    if (input.empty()) {
        result.command = InputCommand::INVALID;
        return result;
    }

    std::string lowerInput = toLower(input);
    if (lowerInput == "quit" || lowerInput == "q") {
        result.command = InputCommand::QUIT;
    } else  if (parseInt(lowerInput, n)) {
        result.command = InputCommand::SELECT_FROM_MENU;
        result.order = n;
    } else {
        result.command = InputCommand::INVALID;
    }

    return result;
}
*/