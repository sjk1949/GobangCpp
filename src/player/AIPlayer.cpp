#include "player/AIPlayer.h"

InputResult AIPlayer::getCommand(Board& board, PieceType type) {
    InputResult out;
    out.command = InputCommand::PLACE_PIECE;
    out.pos = calculateMove(board, type);
    return out;
}