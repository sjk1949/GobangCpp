#include "player/Player.hpp"

#include <string>

Player::Player(std::string name, AIStrategy strategy) : name(name), ai(AI(strategy)) {}

std::string Player::getName() const {
    return name;
}

/*
Pos Player::calculateMove(Board& board, PieceType aiPiece) {
    return ai.calculateMove(board, aiPiece);
}
*/

void Player::push(std::unique_ptr<GameCommand> command) {
    commandBuffer = std::move(command);
}