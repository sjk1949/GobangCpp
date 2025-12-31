#pragma once

#include <vector>
#include "core/Pos.hpp"
#include "core/LineInfo.hpp"

/**
 * @class LinePattern
 * @brief 这个类代表着棋盘上的几个位置的集合，可以用它来表示一种棋型
 */
class LinePattern
{
public:
    LinePattern() = default;
    LinePattern(const LineInfo& info);

    bool operator==(const LinePattern& other) const;
    bool operator!=(const LinePattern& other) const;

    /**
     * @brief 加入一颗在棋盘上已有的棋子，并按照字典序排列
     */
    LinePattern& addPos(Pos pos);

    /**
     * @brief 去除掉棋型模式中的指定点
     */
    LinePattern& removePos(Pos pos);

    bool isEmpty();

private:
    std::vector<Pos> posList; // 线条包含的所有点，有序且没有重复
};