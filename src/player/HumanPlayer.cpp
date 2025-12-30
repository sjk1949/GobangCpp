#include "player/HumanPlayer.hpp"

HumanPlayer::HumanPlayer(std::string name, AIStrategy strategy) : Player(name, strategy) {}

std::unique_ptr<GameCommand> HumanPlayer::getCommand(Board& board, PieceType type) {
    std::unique_ptr<GameCommand> command = std::move(commandBuffer);
    commandBuffer = nullptr;
    return std::move(command);
}