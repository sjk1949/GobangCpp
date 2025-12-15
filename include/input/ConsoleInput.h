#pragma once

#include "InputDevice.h"

class ConsoleInput : public InputDevice
{
public:
    ConsoleInput() = default;
    ///~ConsoleInput() override = default;
    InputResult getMenuInput() override;
    InputResult getInput() override;
    std::string getInput(const std::string& str) override;

private:
    /* 解析字符串输入 */
    InputResult parseMenuInput(const std::string& input);
    /* 解析字符串输入 */
    InputResult parseInput(const std::string& input);
    /* 将字符和数字输入解析成棋盘坐标 */
    Pos parsePos(const char& c, const int& num);
    /* 将字符串格式化为小写字母，参考自DeepSeek */
    std::string toLower(const std::string& str);
    /* 如果可以的话，将字符串解析为一个数字和一个字母的组合，不分先后，并返回true */
    bool parseStringRegex(const std::string& str, char& c, int& num);
    /* 如果可以的话，将字符串解析为纯数字，并返回true */
    bool parseInt(const std::string& str, int& num);
};