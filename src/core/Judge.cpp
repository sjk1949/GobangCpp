#include "core/Judge.hpp"

#include "core/Board.hpp"
#include "core/LineInfo.hpp"

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

std::array<ChessPatternType, 4> Judge::analyse(const Board& board, Pos pos, PieceType type) {
    std::array<ChessPatternType, 4> patterns;
    int i = 0;
    for (LineInfo info : LineInfo::getAllLines(board, pos, type)) {
        patterns[i] = analyse(board, info, type);
        i++;
    }
    return patterns;
}

ChessPatternType Judge::analyse(const Board& board, LineInfo info, PieceType type) {
    if (isOverLine(board, info, type)) {
        return ChessPatternType::OVERLINE;
    } else if (isFive(board, info, type)) {
        return ChessPatternType::FIVE;
    } else if (isLiveFour(board, info, type)) {
        return ChessPatternType::LIVE_FOUR;
    } else if (isFour(board, info, type)) {
        return ChessPatternType::SLEEP_FOUR;
    } else if (isLiveThree(board, info, type)) {
        return ChessPatternType::LIVE_THREE;
    }
    return ChessPatternType::NONE;
}

bool Judge::isLiveThree(const Board& board, LineInfo info, PieceType type) {
    return canBecomeLiveFour(board, info, type);
}

bool Judge::canBecomeLiveFour(const Board& board, LineInfo info, PieceType type) {
    for (Pos pos : info.extension) {
        Board newBoard = board.afterDrop(pos, type);
        LineInfo newInfo = LineInfo::checkLine(newBoard, pos, info.dir);
        if (isLiveFour(newBoard, newInfo, type)) {
            return true;
        }
    }
    return false;
}

bool Judge::isLiveFour(const Board& board, LineInfo info, PieceType type) {
    if (canBecomeFiveNum(board, info, type) >= 2) {
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

ForbiddenType Judge::checkForbidden(const Board& board, Pos pos) {
    if (checkFive(board, pos)) { // 如果同时出现五连和其他禁手，禁手失效
        return ForbiddenType::NONE;
    } else if (checkOverLine(board, pos)) {
        return ForbiddenType::OVERLINE;
    } else if (checkDoubleFour(board, pos)) {
        return ForbiddenType::DOUBLE_FOUR;
    } else if (checkDoubleThree(board, pos)) {
        return ForbiddenType::DOUBLE_THREE;
    }
    return ForbiddenType::NONE;
}

bool Judge::isForbidden(const Board& board, Pos pos) {
    return checkForbidden(board, pos) != ForbiddenType::NONE;
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
            if (!isForbidden(pattern.board, pos)) {
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
            if (!isForbidden(pattern.board, pos)) {
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