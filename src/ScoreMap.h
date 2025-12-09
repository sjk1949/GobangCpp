#pragma once

#include "Object.h"

#include <array>
#include <sstream>
#include <iomanip>
#include "Pos.h"
#include "Board.h"

class ScoreMap : public Object
{
public:
    int getScore(Pos pos) const {return scoreMap[pos.x][pos.y];}
    void setScore(Pos pos, int score) {scoreMap[pos.x][pos.y] = score;}
    static ScoreMap createEmptyScoreMap() {
        ScoreMap emptyMap;
        for (auto& row : emptyMap.scoreMap) {
            for (auto& score : row) {
                score = 0;
            }
        }
        return emptyMap;
    }
    std::string toString() const override {
        std::stringstream ss;
        for (int i = 0; i < scoreMap.size(); i++) {
            ss << std::setw(2) << scoreMap.size() - i;
            for (int j = 0; j < scoreMap.size(); j++) {
                ss << std::setw(3) << getScore(Pos(i, j));
            }
            ss << std::endl;
        }
        ss << "   ";
        for (int i = 0; i < scoreMap.size(); i++) {
            ss << " " << char('A' + i) << " ";
        }
        return ss.str();
    }
private:
    /* AI对棋盘空位置的计算分数图 */
    std::array<std::array<int, Board::BOARD_SIZE>, Board::BOARD_SIZE> scoreMap;
};