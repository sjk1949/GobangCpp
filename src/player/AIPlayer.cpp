#include "player/AIPlayer.hpp"

AIPlayer::AIPlayer(std::string name, AIStrategy strategy) : Player(name, strategy, true) {}

std::unique_ptr<GameCommand> AIPlayer::getCommand(Board& board, PieceType type) {
    return std::make_unique<PlacePieceCommand>(ai.calculateMove(board, type));
}