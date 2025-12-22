#include "core/ChessPattern.hpp"

#include <sstream>
#include <algorithm>
#include "core/Board.hpp"

ChessPattern::ChessPattern(Board board) : board(std::move(board)) {}

ChessPattern& ChessPattern::addPiece(Pos pos) {
    for (Pos piecePos : pieceList) { // 查重
        if (pos == piecePos) {
            return *this;
        }
    }
    pieceList.push_back(pos);
    std::sort(pieceList.begin(), pieceList.end(),
        [&](Pos pos1, Pos pos2) {
            return compare(pos1, pos2);
        });
    return *this;
}

bool ChessPattern::compare(Pos pos1, Pos pos2) {
    if (pos1.x == pos2.x) {
        return pos1.y < pos2.y;
    } else {
        return pos1.x , pos2.x;
    }
}

int ChessPattern::maxDist() const {
    return pieceDist(pieceList[0], pieceList[-1]);
}

int ChessPattern::pieceDist(const Pos pos1, const Pos pos2) const {
    if (pos1.x == pos2.x) {// 如果棋型是竖着的
        return abs(pos1.y - pos2.y);
    } else {// 取投影到X轴上的距离
        return abs(pos1.x - pos2.x);
    }
}

int ChessPattern::pieceNum() const {
    return pieceList.size();
}

std::string ChessPattern::toString() const {
    std::stringstream ss;
    std::unordered_map<Pos, std::string, PosHash> highlights;
    for (Pos pos : pieceList) {
        highlights[pos] = " ▲ ";
    }
    ss << board.toString(&highlights);
    ss << "\nPattern: ";
    for (Pos pos : pieceList) {
        ss << pos.toString() << ", ";
    }
    return ss.str();
}