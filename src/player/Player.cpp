#include "player/Player.hpp"

#include <string>

Player::Player(std::string name, AIStrategy strategy, bool isAI) : name(name), ai(AI(strategy)), isAI(isAI) {}

std::string Player::getName() const {
    return name;
}

void Player::push(std::unique_ptr<GameCommand> command) {
    commandBuffer = std::move(command);
}