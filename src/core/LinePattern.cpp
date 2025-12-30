#include "core/LinePattern.hpp"

#include <algorithm>

LinePattern::LinePattern(const LineInfo& info) {
    for (Pos pos : info.posList) {
        addPos(pos);
    }
}

bool LinePattern::operator==(const LinePattern& other) const {
    return posList == other.posList;
}

bool LinePattern::operator!=(const LinePattern& other) const {
    return !(*this == other);
}

LinePattern& LinePattern::addPos(Pos pos) {
    for (Pos item : posList) { // 查重
        if (pos == item) {
            return *this;
        }
    }
    posList.push_back(pos);
    std::sort(posList.begin(), posList.end(),
        [&](Pos pos1, Pos pos2) {
            return pos1 < pos2;
        });
    return *this;
}

LinePattern& LinePattern::removePos(Pos pos) {
    for (auto it = posList.begin(); it != posList.end();) {
        if (*it == pos) {
            it = posList.erase(it);
        } else {
            it++;
        }
    }
    return *this;
}

bool LinePattern::isEmpty() {
    return posList.size() == 0;
}