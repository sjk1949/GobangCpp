#include "player/AIPlayer.h"

PlayerAction AIPlayer::getAction(Board& board, PieceType type) {
    return {ActionType::PLACE_PIECE, calculateMove(board, type)};
}