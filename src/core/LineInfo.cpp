#include "core/LineInfo.hpp"

#include <iomanip>

LineInfo LineInfo::getLongestLine(const Board& board, Pos pos) {
    return getLongestLine(board, pos, board.getPos(pos));
}

LineInfo LineInfo::getLongestLine(const Board& board, Pos pos, PieceType type) {
    LineInfo longestLine;
    for (LineInfo info : getAllLines(board, pos, type)) {
        if (info.length >= longestLine.length) {
            longestLine = info;
        }
    }
    return longestLine;
}

std::array<LineInfo, 4> LineInfo::getAllLines(const Board& board, Pos pos) {
    return getAllLines(board, pos, board.getPos(pos));
}

std::array<LineInfo, 4> LineInfo::getAllLines(const Board& board, Pos pos, PieceType type) {
    std::array<LineInfo, 4> result;
    result[0] = checkLine(board, pos, Dir::HORIZONTAL, type);
    result[1] = checkLine(board, pos, Dir::VERTICAL, type);
    result[2] = checkLine(board, pos, Dir::RIGHTUP, type);
    result[3] = checkLine(board, pos, Dir::RIGHTDOWN, type);
    return result;
}

LineInfo LineInfo::checkLine(const Board& board, Pos pos, Dir dir) {
    return mergeLineInfo(checkLineToDir(board, pos, dir, false), checkLineToDir(board, pos, dir, true));
}

LineInfo LineInfo::checkLine(const Board& board, Pos pos, Dir dir, PieceType type) {
    return mergeLineInfo(checkLineToDir(board, pos, dir, false, type), checkLineToDir(board, pos, dir, true, type));
}

LineInfo LineInfo::checkLineToDir(const Board& board, Pos pos, Dir dir, bool isForward) {
    return checkLineToDir(board, pos, dir, isForward, board.getPos(pos));
}

LineInfo LineInfo::checkLineToDir(const Board& board, Pos pos, Dir dir, bool isForward, PieceType type) {
    LineInfo info;
    info.dir = dir;
    if (type == PieceType::EMPTY) {
        return info;
    } else {
        int forward = (isForward) ? 1 : -1;
        Pos currPos = pos; //当前检查的位置
        info.length += 1;
        currPos += (Pos::toPos(dir) *= forward);
        for (; board.isOnBoard(currPos) && board.getPos(currPos) == type; currPos += (Pos::toPos(dir) *= forward)) {
            info.length += 1;
        }
        if (board.isOnBoard(currPos) && board.getPos(currPos) == PieceType::EMPTY) {
            info.openEnds[0] = true;
            info.openEnds[1] = true;
            info.extension.push_back(currPos);
        }
        return info;
    }
}

PatternType LineInfo::parsePatten(LineInfo lineInfo) {
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

LineInfo LineInfo::mergeLineInfo(LineInfo info1, LineInfo info2) {
    LineInfo info;
    if (info1.dir != info2.dir) {
        throw std::invalid_argument("两个参数的Dir必须一致!");
    }
    info.dir = info1.dir;
    info.length = info1.length + info2.length - 1;
    info.openEnds[0] = info1.openEnds[0];
    info.openEnds[1] = info2.openEnds[0];
    std::vector<Pos> extension;
    extension.insert(extension.end(), info1.extension.begin(), info1.extension.end());
    extension.insert(extension.end(), info2.extension.begin(), info2.extension.end());
    info.extension = extension;
    return info;
}

std::string LineInfo::toString() const {
    std::string str = "LineInfo@";
    str += "length: " + std::to_string(length) + "\n";
    str += "openEnds: " + std::to_string(openEnds[0]) + ", " + std::to_string(openEnds[1]) + "\n";
    str += "Extension Points: ";
    for (Pos pos : extension) {
        str += pos.toString();
        str += ", ";
    }
    str += "\nDirection: " + Pos::toPos(dir).toString();
    
    return str;
}