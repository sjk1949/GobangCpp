#include "utils/ScoreMap.hpp"

#include <cmath>
#include <sstream>
#include <iomanip>

ScoreMap ScoreMap::createEmptyScoreMap() {
    ScoreMap emptyMap;
    for (auto& row : emptyMap.scoreMap) {
        for (auto& score : row) {
            score = 0;
        }
    }
    return emptyMap;
}

void ScoreMap::initScoreMap() {
    const int boardSize = scoreMap.size();
    const int center = boardSize / 2;

    float sigma = boardSize / 3; //标准差，控制衰减速度
    float amplitude = 100.0; //中心峰值，即最大分数

    for (int x = 0; x < boardSize; x++) {
        for (int y = 0; y < boardSize; y++) {
            float dx = x - center;
            float dy = y - center;
            float squareDist = dx * dx + dy * dy;

            float score = amplitude * exp(-squareDist / (2.0 * sigma * sigma));
            setScore(Pos(x, y), static_cast<int>(score));
        }
    }
}

Pos ScoreMap::findMax() {
    Pos maxPos = Pos(0, 0);
    int max = getScore(maxPos);
    for (int i = 0; i < scoreMap.size(); i++) {
        for (int j = 0; j < scoreMap.size(); j++) {
            int score = getScore(Pos(i, j));
            if (score > max) {
                maxPos = Pos(i, j);
                max = score;
            }
        }
    }
    return maxPos;
}

std::string ScoreMap::toString() const {
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