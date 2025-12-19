#include "player/HumanPlayer.h"

InputResult HumanPlayer::getCommand(Board& board, PieceType type) {
    InputResult out = result;
    result.command = InputCommand::NONE;
    return out;
}