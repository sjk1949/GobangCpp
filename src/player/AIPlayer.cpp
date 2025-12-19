#include "player/AIPlayer.h"

std::unique_ptr<GameCommand> AIPlayer::getCommand(Board& board, PieceType type) {
    return std::make_unique<PlacePieceCommand>(calculateMove(board, type));
}