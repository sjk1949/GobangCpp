#include "core/GameHistory.hpp"

void GameHistory::addMove(Move move) {
    moveList.push_back(move);
}

bool GameHistory::canUndo() {
    return !moveList.empty();
}

Move GameHistory::undoLastMove() {
    Move move = moveList.back();
    moveList.pop_back();
    return move;
}