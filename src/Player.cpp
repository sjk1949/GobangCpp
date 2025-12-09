#include "Player.h"

#include <string>

Player::Player(std::string name) : name(name) {}

std::string Player::getName() const {
    return name;
}

Pos Player::calculateMove(Board& board, PieceType aiPiece) {
    return ai.calculateMove(board, aiPiece);
}