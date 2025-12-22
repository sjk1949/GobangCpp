#include <array>
#include <sstream>
#include <iomanip>

#include "core/Board.hpp"
#include "core/GameTypes.hpp"

Board::Board() {
    clearBoard();
}

Board Board::createEmptyBoard() {
    return Board();
}

int Board::rowToPosY(int row) {
    return BOARD_SIZE - row;
}

bool Board::isOnBoard(Pos pos) {
    return pos.x >= 0 && pos.x < BOARD_SIZE && pos.y >= 0 && pos.y < BOARD_SIZE;
}

PieceType Board::getPos(Pos pos) const {
    return board[pos.x][pos.y];
}

bool Board::setPos(Pos pos, PieceType type) {
    board[pos.x][pos.y] = type;
    return true;
}

bool Board::isEmpty(Pos pos) {
    return getPos(pos) == PieceType::EMPTY;
}

LineInfo Board::getLongestLine(Pos pos) const {
    return getLongestLine(pos, getPos(pos));
}

LineInfo Board::getLongestLine(Pos pos, PieceType type) const {
    LineInfo longestLine;
    for (LineInfo info : getAllLines(pos, type)) {
        if (info.length >= longestLine.length) {
            longestLine = info;
        }
    }
    return longestLine;
}


std::array<LineInfo, 4> Board::getAllLines(Pos pos) const {
    return getAllLines(pos, getPos(pos));
}

std::array<LineInfo, 4> Board::getAllLines(Pos pos, PieceType type) const {
    std::array<LineInfo, 4> result;
    result[0] = checkLine(pos, Dir::HORIZONTAL, type);
    result[1] = checkLine(pos, Dir::VERTICAL, type);
    result[2] = checkLine(pos, Dir::RIGHTUP, type);
    result[3] = checkLine(pos, Dir::RIGHTDOWN, type);
    return result;
}

LineInfo Board::checkLine(Pos pos, Dir dir) const {
    return mergeLineInfo(checkLineToDir(pos, dir, false), checkLineToDir(pos, dir, true));
}

LineInfo Board::checkLine(Pos pos, Dir dir, PieceType type) const {
    return mergeLineInfo(checkLineToDir(pos, dir, false, type), checkLineToDir(pos, dir, true, type));
}

LineInfo Board::checkLineToDir(Pos pos, Dir dir, bool isForward) const {
    return checkLineToDir(pos, dir, isForward, getPos(pos));
}

LineInfo Board::checkLineToDir(Pos pos, Dir dir, bool isForward, PieceType type) const {
    LineInfo info;
    info.dir = dir;
    if (type == PieceType::EMPTY) {
        return info;
    } else {
        int forward = (isForward) ? 1 : -1;
        Pos currPos = pos; //当前检查的位置
        info.length += 1;
        currPos += (Pos::toPos(dir) *= forward);
        for (; isOnBoard(currPos) && getPos(currPos) == type; currPos += (Pos::toPos(dir) *= forward)) {
            info.length += 1;
        }
        if (isOnBoard(currPos) && getPos(currPos) == PieceType::EMPTY) {
            info.openEnds[0] = true;
            info.openEnds[1] = true;
        }
        return info;
    }
}

PatternType Board::parsePatten(LineInfo lineInfo) {
    int openEnds = 0;
    if (lineInfo.openEnds[0] == true) {openEnds += 1;}
    if (lineInfo.openEnds[1] == true) {openEnds += 1;}
    switch (lineInfo.length)
    {
    case 5:
        return PatternType::FIVE;
    case 4:
        switch (openEnds)
        {
        case 2:
            return PatternType::LIVE_FOUR;
        case 1:
            return PatternType::SLEEP_FOUR;
        case 0:
            return PatternType::BLOCK_FOUR;
        }
    case 3:
        switch (openEnds)
        {
        case 2:
            return PatternType::LIVE_THREE;
        case 1:
            return PatternType::SLEEP_THREE;
        case 0:
            return PatternType::BLOCK_THREE;
        }
    case 2:
        switch (openEnds)
        {
        case 2:
            return PatternType::LIVE_TWO;
        case 1:
            return PatternType::SLEEP_TWO;
        case 0:
            return PatternType::BLOCK_TWO;
        }
    case 1:
        return PatternType::ONE;   
    default:
        if (lineInfo.length > 5) {
            return PatternType::OVERLINE;
        }
        return PatternType::INVALID;
    }
}

void Board::clearBoard() {
    for (int i = 0; i < Board::BOARD_SIZE; i++) {
        for (int j = 0; j < Board::BOARD_SIZE; j++) {
            setPos(Pos(i, j), PieceType::EMPTY);
        }
    }
}

LineInfo Board::mergeLineInfo(LineInfo info1, LineInfo info2) const {
    LineInfo info;
    if (info1.dir != info2.dir) {
        throw std::invalid_argument("两个参数的Dir必须一致!");
    }
    info.dir = info1.dir;
    info.length = info1.length + info2.length - 1;
    info.openEnds[0] = info1.openEnds[0];
    info.openEnds[1] = info2.openEnds[0];
    return info;
}

PieceType Board::opponentOf(PieceType type) {
    return (type == PieceType::BLACK) ? PieceType::WHITE : PieceType::BLACK;
}

std::string Board::toString() const {
    std::stringstream ss;
    for (int i = BOARD_SIZE; i >= 1; i--) {
        ss << std::setw(2) << i << toStringRow(i) << "\n";
    }
    ss << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        ss << " " << char('A' + i) << " ";
    }
    return ss.str();
}

std::string Board::toString(const std::unordered_map<Pos, std::string, PosHash>* highlights) const {
    std::stringstream ss;
    for (int i = BOARD_SIZE; i >= 1; i--) {
        ss << std::setw(2) << i << toStringRow(i, highlights) << "\n";
    }
    ss << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        ss << " " << char('A' + i) << " ";
    }
    return ss.str();
}

std::string Board::pieceToString(const PieceType type) const {
    switch (type)
    {
    case PieceType::EMPTY:
        return " . ";
    case PieceType::BLACK:
        return " ● ";
    case PieceType::WHITE:
        return " ○ ";
    default:
        return " ? ";
    }
}

/*
std::string Board::toStringRow(int row) const {
    std::stringstream ss;
    for (int i = 0; i < BOARD_SIZE; i++) {
        switch (getPos(Pos(i, BOARD_SIZE - row)))
        {
        case PieceType::EMPTY:
            ss << " . ";
            break;
        case PieceType::BLACK:
            ss << " ● ";
            break;
        case PieceType::WHITE:
            ss << " ○ ";
            break;
        default:
            ss << " ? ";
            break;
        }
    }
    return ss.str();
}
    */

std::string Board::toStringRow(int row, const std::unordered_map<Pos, std::string, PosHash>* highlights) const {
    std::stringstream ss;
    for (int i = 0; i < BOARD_SIZE; i++) {
        Pos pos(i, BOARD_SIZE - row);
        if (highlights && highlights->count(pos)) {
            ss << (*highlights).at(pos);
        } else {
            ss << pieceToString(getPos(pos));
        }
    }
    return ss.str();
}