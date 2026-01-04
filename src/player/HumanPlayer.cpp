#include "player/HumanPlayer.hpp"

HumanPlayer::HumanPlayer(std::string name, AIStrategy strategy) : Player(name, strategy, false) {}

std::unique_ptr<GameCommand> HumanPlayer::getCommand(Board& board, PieceType type) {
    std::unique_ptr<GameCommand> command = std::move(commandBuffer);
    commandBuffer = nullptr;
    return std::move(command);
}