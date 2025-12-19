#include "player/Player.h"

#include <string>

Player::Player(std::string name) : name(name) {}

std::string Player::getName() const {
    return name;
}

Pos Player::calculateMove(Board& board, PieceType aiPiece) {
    return ai.calculateMove(board, aiPiece);
}

void Player::push(InputResult result) {
    this->result = result;
}

bool Player::hasCommand() {
    return result.command != InputCommand::NONE;
}