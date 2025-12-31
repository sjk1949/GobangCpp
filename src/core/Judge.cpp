#include "core/Judge.hpp"

#include <map>
#include "core/Board.hpp"
#include "core/LineInfo.hpp"
#include "core/LinePattern.hpp"

bool Judge::isValidMove(const Board& board, const Pos pos) {
    if (Board::isOnBoard(pos) && board.getPos(pos) == PieceType::EMPTY) {
        return true;
    }
    return false;
}

GameResult Judge::ckeckWin(const Board& board, Pos lastDrop) {
    if (LineInfo::getLongestLine(board, lastDrop).length >= 5) {
        return (board.getPos(lastDrop) == PieceType::BLACK) ? GameResult::BLACK_WIN : GameResult::WHITE_WIN;
    }
    return GameResult::NO_WINNER;
}

std::array<std::vector<ChessPatternType>, 4> Judge::analyse(const Board& board, Pos pos, PieceType type) {
    std::array<std::vector<ChessPatternType>, 4> patterns;
    int i = 0;
    for (LineInfo info : LineInfo::getAllLines(board, pos, type)) {
        patterns[i] = analyse(board, info, type);
        i++;
    }
    return patterns;
}

std::vector<ChessPatternType> Judge::analyse(const Board& board, LineInfo info, PieceType type) {
    std::vector<ChessPatternType> patternList;
    if (isOverLine(board, info, type)) {
        patternList.push_back(ChessPatternType::OVERLINE);
    } else if (isFive(board, info, type)) {
        patternList.push_back(ChessPatternType::FIVE);
    } else if (isFour(board, info, type)) {
        std::vector<ChessPatternType> fourList = analyseFour(board, info, type);
        patternList.insert(patternList.end(), fourList.begin(), fourList.end());
    } else if (isLiveThree(board, info, type)) {
        patternList.push_back(ChessPatternType::LIVE_THREE);
    }
    return patternList;
}

bool Judge::isLiveThree(const Board& board, LineInfo info, PieceType type) {
    return canBecomeLiveFour(board, info, type);
}

bool Judge::canBecomeLiveFour(const Board& board, LineInfo info, PieceType type) {
    for (Pos pos : info.extension) {
        // @todo 检查落点是否合法 目前会导致死循环
        //if (isForbidden(board, pos, type)) {continue;}
        Board newBoard = board.afterDrop(pos, type);
        LineInfo newInfo = LineInfo::checkLine(newBoard, pos, info.dir);
        if (isLiveFour(newBoard, newInfo, type)) {
            return true;
        }
    }
    return false;
}

bool Judge::isLiveFour(const Board& board, LineInfo info, PieceType type) {
    // 如果能成两个5，一定就是活四吗？不一定，如果两个五除了成五的落子外并不完全相同，那就是(双)冲四了，比如EBEBBBEBE
    //if (canBecomeFiveNum(board, info, type) >= 2) {
    int fiveNum = 0;
    LinePattern lastOldPattern;
    for (Pos pos : info.extension) {
        Board newBoard = board.afterDrop(pos, type);
        LineInfo newInfo = LineInfo::checkLine(newBoard, pos, info.dir);
        if (isFive(newBoard, newInfo, type)) {
            LinePattern oldPattern = LinePattern(newInfo).removePos(pos);
            if (lastOldPattern.isEmpty()) {
                lastOldPattern = oldPattern;
            } else if (oldPattern != lastOldPattern) { // 已经出现过五连，但是这次构成五连的四连和上次有区别
                return false; // 两个冲四的情况
            }
            fiveNum++;
        }
    }
    if (fiveNum >= 2) {
        return true;
    }
    return false;
}

bool  Judge::isFour(const Board& board, LineInfo info, PieceType type) {
    if (canBecomeFive(board, info, type)) {
        return true;
    }
    return false;
}

std::vector<ChessPatternType> Judge::analyseFour(const Board& board, LineInfo info, PieceType type) {
    std::vector<ChessPatternType> result;

    int fiveNum = 0;
    LinePattern lastOldPattern;
    for (Pos pos : info.extension) {
        Board newBoard = board.afterDrop(pos, type);
        LineInfo newInfo = LineInfo::checkLine(newBoard, pos, info.dir);
        if (isFive(newBoard, newInfo, type)) {
            LinePattern oldPattern = LinePattern(newInfo).removePos(pos);
            if (lastOldPattern.isEmpty()) {
                lastOldPattern = oldPattern;
            } else if (oldPattern != lastOldPattern) { // 已经出现过五连，但是这次构成五连的四连和上次有区别
                fiveNum = 0; // 这是上一个冲四的Num，将其清空
                result.push_back(ChessPatternType::SLEEP_FOUR);// 两个冲四的情况
            }
            fiveNum++;
        }
    }
    if (fiveNum >= 2) {
        result.push_back(ChessPatternType::LIVE_FOUR);
    } else if (fiveNum == 1) {
        result.push_back(ChessPatternType::SLEEP_FOUR);
    }
    return result;
}

bool Judge::canBecomeFive(const Board& board, LineInfo info, PieceType type) {
    if (canBecomeFiveNum(board, info, type) > 0) {
        return true;
    }
    return false;
}

int Judge::canBecomeFiveNum(const Board& board, LineInfo info, PieceType type) {
    int fiveNum = 0;
    for (Pos pos : info.extension) {
        Board newBoard = board.afterDrop(pos, type);
        LineInfo newInfo = LineInfo::checkLine(newBoard, pos, info.dir);
        if (isFive(newBoard, newInfo, type)) {
            fiveNum++;
        }
    }
    return fiveNum;
}

bool Judge::isFive(const Board& board, LineInfo info, PieceType type) {
    if (info.length == 5) {
        return true;
    }
    return false;
}

bool Judge::isOverLine(const Board& board, LineInfo info, PieceType type) {
    if (info.length > 5) {
        return true;
    }
    return false;
}

bool Judge::checkFive(const Board& board, Pos pos) {
    for (auto lineInfo : LineInfo::getAllLines(board, pos)) {
        if (lineInfo.length == 5) {
            return true;
        }
    }
    return false;
}

bool Judge::checkOverLine(const Board& board, Pos pos) {
    if (LineInfo::getLongestLine(board, pos).length > 5) {
        return true;
    }
    return false;
}

bool Judge::checkDoubleFour(const Board& board, Pos pos) {
    return false;
}

bool Judge::checkDoubleThree(const Board& board, Pos pos) {
    return false;
}

ForbiddenType Judge::checkForbidden(const Board& board, Pos pos, PieceType type) {
    if (type != PieceType::BLACK) {
        return ForbiddenType::NONE;
    }
    Board newBoard = board.afterDrop(pos, type);
    // @todo 简单分析排除
    // 接下来这一步需要大量的分析，以及递归(如果适用的话)，所以如无必要，优先排除简单情况
    std::array<std::vector<ChessPatternType>, 4> patternList = analyse(newBoard, pos, type); // 分析的是假设落子后的棋盘，注意！
    std::map<ChessPatternType, int> dict = countPattern(patternList);
    if (dict[ChessPatternType::FIVE] > 0) { // 如果同时出现五连和其他禁手，禁手失效
        return ForbiddenType::NONE;
    } else if (dict[ChessPatternType::OVERLINE] > 0) {
        return ForbiddenType::OVERLINE;
    } else if (dict[ChessPatternType::LIVE_FOUR] + dict[ChessPatternType::SLEEP_FOUR] >= 2) {
        return ForbiddenType::DOUBLE_FOUR;
    } else if (dict[ChessPatternType::LIVE_THREE] >= 2) {
        return ForbiddenType::DOUBLE_THREE;
    }
    return ForbiddenType::NONE;
}

bool Judge::isForbidden(const Board& board, Pos pos, PieceType type) {
    return checkForbidden(board, pos, type) != ForbiddenType::NONE;
}

std::map<ChessPatternType, int> Judge::countPattern(std::array<std::vector<ChessPatternType>, 4> patternList) {
    //生成空字典
    std::map<ChessPatternType, int> dict = {
        {ChessPatternType::OVERLINE, 0},
        {ChessPatternType::FIVE, 0},
        {ChessPatternType::LIVE_FOUR, 0},
        {ChessPatternType::SLEEP_FOUR, 0},
        {ChessPatternType::LIVE_THREE, 0},
        {ChessPatternType::NONE, 0}
    };
    for (const auto& pattern : patternList) {
        for (auto type : pattern) {
            dict[type]++;
        }
    }
    return dict;
}

ChessPatternType Judge::checkChessPatternType(const ChessPattern& pattern) {
    if (pattern.maxDist() >= 5) {
        if (pattern.maxDist() + 1 == pattern.pieceNum()) {
            return ChessPatternType::OVERLINE;
        } else { // 按理来说不会出现这种情况
            return ChessPatternType::NONE;
        }
    } else if (pattern.maxDist() == 4 && pattern.pieceNum() == 5) {
        return ChessPatternType::FIVE;
    }
    // @todo
    if (pattern.pieceNum() == 4) { // 是某种四
        int fiveNumber = 0;
        for (Pos pos : searchForAvailablePos(pattern)) {
            if (!isForbidden(pattern.board, pos, pattern.pieceType)) {
                ChessPattern newPattern = pattern;
                newPattern.placePiece(pos);
                if (checkChessPatternType(newPattern) == ChessPatternType::FIVE) {
                    fiveNumber++;
                }
            }
        }
        switch (fiveNumber) {
            case 2:
                return ChessPatternType::LIVE_FOUR;
            case 1:
                return ChessPatternType::SLEEP_FOUR;
            case 0:
                return ChessPatternType::NONE;
        }
    }
    if (pattern.pieceNum() == 3) { // 是某种三
        for (Pos pos : searchForAvailablePos(pattern)) {
            if (!isForbidden(pattern.board, pos, pattern.pieceType)) {
                ChessPattern newPattern = pattern;
                newPattern.placePiece(pos);
                if (checkChessPatternType(newPattern) == ChessPatternType::LIVE_FOUR) { // 只要有一种能成活四， 便是活三
                    return ChessPatternType::LIVE_THREE;
                }
            }
        }
    }
    return ChessPatternType::NONE;
}

std::string Judge::chessPatternTypeToString(ChessPatternType type) {
    switch (type)
    {
    case ChessPatternType::OVERLINE:
        return "OVERLINE";
    case ChessPatternType::FIVE:
        return "FIVE";
    case ChessPatternType::LIVE_FOUR:
        return "LIVE_FOUR";
    case ChessPatternType::SLEEP_FOUR:
        return "SLEEP_FOUR";
    case ChessPatternType::LIVE_THREE:
        return "LIVE_THREE";
    case ChessPatternType::NONE:
        return "NONE";
    default:
        return "?";
    }
}

std::string Judge::forbiddenTypeToString(ForbiddenType type) {
    switch (type)
    {
    case ForbiddenType::NONE:
        return "NONE";
    case ForbiddenType::OVERLINE:
        return "OVERLINE";
    case ForbiddenType::DOUBLE_FOUR:
        return "DOUBLE_FOUR";
    case ForbiddenType::DOUBLE_THREE:
        return "DOUBLE_THREE";
    default:
        return "?";
    }
}