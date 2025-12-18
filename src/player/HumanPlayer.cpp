#include "player/HumanPlayer.h"

HumanPlayer::HumanPlayer(InputDevice& input) : input(input) {}

/*
PlayerAction HumanPlayer::getAction(Board& board, PieceType type) {
    PlayerAction action;
    // @todo 将Player和输入解耦
    switch (result.command)
    {
    case InputCommand::PLACE_PIECE:
        return {ActionType::PLACE_PIECE, result.pos};
    case InputCommand::QUIT:
        return {ActionType::QUIT};
    default:
        return {ActionType::INVALID};
    }
}
    */