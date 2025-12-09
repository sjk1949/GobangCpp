#include <array>
#include <sstream>
#include <iomanip>

#include "Board.h"
#include "GameTypes.h"

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
    LineInfo longestLine;
    for (LineInfo info : getAllLines(pos)) {
        if (info.length >= longestLine.length) {
            longestLine = info;
        }
    }
    return longestLine;
}

std::array<LineInfo, 4> Board::getAllLines(Pos pos) const {
    std::array<LineInfo, 4> result;
    result[0] = checkLine(pos, Dir::HORIZONTAL);
    result[1] = checkLine(pos, Dir::VERTICAL);
    result[2] = checkLine(pos, Dir::RIGHTUP);
    result[3] = checkLine(pos, Dir::RIGHTDOWN);
    return result;
}

LineInfo Board::checkLine(Pos pos, Dir dir) const {
    return mergeLineInfo(checkLineToDir(pos, dir, false), checkLineToDir(pos, dir, true));
}

LineInfo Board::checkLineToDir(Pos pos, Dir dir, bool isForward) const {
    LineInfo info;
    info.dir = dir;
    PieceType type = getPos(pos);
    if (type == PieceType::EMPTY) {
        return info;
    } else {
        int forward = (isForward) ? 1 : -1;
        Pos currPos = pos; //当前检查的位置
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

std::string Board::toString() const {
    std::stringstream ss;
    for (int i = BOARD_SIZE; i >= 1; i--) {
        ss << std::setw(2) << i << toStringRow(i) << std::endl;
    }
    ss << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        ss << " " << char('A' + i) << " ";
    }
    return ss.str();
}

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