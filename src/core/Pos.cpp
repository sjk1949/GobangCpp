#include <stdexcept>

#include "core/Pos.hpp"

Pos::Pos(int x, int y) : x(x), y(y) {}

Pos Pos::operator+(const Pos& other) const {
    return Pos(x + other.x, y + other.y);
}

Pos Pos::operator-(const Pos& other) const {
    return Pos(x - other.x, y - other.y);
}

Pos Pos::operator*(const int scalar) const {
    return Pos(x * scalar, y * scalar);
}

Pos& Pos::operator+=(const Pos& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Pos& Pos::operator-=(const Pos& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Pos& Pos::operator*=(const int scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Pos Pos::toPos(const Dir dir) {
    switch (dir)
    {
    case Dir::HORIZONTAL:
        return Pos(1, 0);
    case Dir::VERTICAL:
        return Pos(0, 1);
    case Dir::LEFT:
        return Pos(-1, 0);
    case Dir::RIGHT:
        return Pos(1, 0);
    case Dir::UP:
        return Pos(0, -1);
    case Dir::DOWN:
        return Pos(0, 1);
    case Dir::LEFTUP:
        return Pos(-1, -1);
    case Dir::LEFTDOWN:
        return Pos(-1, 1);
    case Dir::RIGHTUP:
        return Pos(1, -1);
    case Dir::RIGHTDOWN:
        return Pos(1, 1);
    default:
        throw std::invalid_argument("Invalid direction");
    }
}

Pos& Pos::to(const Dir dir) {
    *this += toPos(dir);
    return *this;
}

std::string Pos::toString() const {
    std::string str = "";
    return str += "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}