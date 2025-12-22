#pragma once

#include "utils/Object.hpp"

/**
 * 这个枚举类表示棋盘上的八种方向
 */
enum class Dir
{
    HORIZONTAL,
    VERTICAL,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    LEFTUP,
    LEFTDOWN,
    RIGHTUP,
    RIGHTDOWN
};

/**
 * 这个类代表棋盘坐标，以棋盘左上角坐标为(0, 0)
 */
class Pos : public Object
{
public:
    /* 将给定方位转化成位移坐标 */
    static Pos toPos(const Dir dir);
    int x;
    int y;
    Pos() = default;
    Pos(int x, int y);
    Pos operator+(const Pos& other) const;
    Pos operator-(const Pos& other) const;
    Pos operator*(const int scalar) const;
    bool operator==(const Pos& other) const;
    Pos& operator+=(const Pos& other);
    Pos& operator-=(const Pos& other);
    Pos& operator*=(const int scalar);
    /* 将给定坐标向给定方向移动一个单位 */
    Pos& to(const Dir dir);
    std::string toString() const override;
};

struct PosHash {
    std::size_t operator()(const Pos& p) const noexcept {
        return (static_cast<std::size_t>(p.x) << 32)
             ^ static_cast<std::size_t>(p.y);
    }
};