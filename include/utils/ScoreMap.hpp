#pragma once

#include "Object.hpp"

#include <array>
#include "core/Pos.hpp"
#include "core/Board.hpp"

class ScoreMap : public Object
{
public:
    int getScore(Pos pos) const {return scoreMap[pos.x][pos.y];}
    void setScore(Pos pos, int score) {scoreMap[pos.x][pos.y] = score;}
    static ScoreMap createEmptyScoreMap();
    /**
     * @brief 根据距离棋盘中心的距离初始化分数图，呈正态分布
     */
    void initScoreMap();
    Pos findMax();

    std::string toString() const override;

private:
    /* AI对棋盘空位置的计算分数图 */
    std::array<std::array<int, Board::BOARD_SIZE>, Board::BOARD_SIZE> scoreMap;
};