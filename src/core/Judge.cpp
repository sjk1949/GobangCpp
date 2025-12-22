#include "core/Judge.hpp"

#include "core/Board.hpp"

bool Judge::isValidMove(const Board& board, const Pos pos) {
    if (Board::isOnBoard(pos) && board.getPos(pos) == PieceType::EMPTY) {
        return true;
    }
    return false;
}

GameResult Judge::ckeckWin(const Board& board, Pos lastDrop) {
    if (board.getLongestLine(lastDrop).length >= 5) {
        return (board.getPos(lastDrop) == PieceType::BLACK) ? GameResult::BLACK_WIN : GameResult::WHITE_WIN;
    }
    return GameResult::NO_WINNER;
}

ChessPatternType Judge::checkChessPatternType(ChessPattern pattern) {
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
    return ChessPatternType::NONE;
}