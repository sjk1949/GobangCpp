#include "core/Game.h"
#include "core/Board.h"
#include "player/HumanPlayer.h"
#include "player/AIPlayer.h"

Game::Game(std::unique_ptr<Player> player1, std::unique_ptr<Player> player2) : board(Board::createEmptyBoard()), judge(Judge()) {
    this -> player1 = std::move(player1);
    this -> player2 = std::move(player2);
    currentPlayer = this -> player1.get();
    state = GameState::PLAYING;
}

GameState Game::run() {
    PlayerAction action = currentPlayer->getAction(board, getPieceType(currentPlayer));
    switch (action.type)
    {
    case ActionType::QUIT:
        state = GameState::QUIT;
        break;
    case ActionType::PLACE_PIECE:
        if (placePiece(action.pos, currentPlayer)) {
            switch (judge.ckeckWin(board, action.pos))
            {
            case GameResult::NO_WINNER:
                changePlayer();
                break;
            case GameResult::BLACK_WIN:
                state = GameState::BLACK_WIN;
                break;
            case GameResult::WHITE_WIN:
                state = GameState::WHITE_WIN;
                break;
            case GameResult::DRAW:
                state = GameState::DRAW;
                break;
            }
        } else {
            setMessage("不能在该处落子！");
        }
        break;
    case ActionType::INVALID:
        setMessage("非法输入");
        break;
    default:
        break;
    }
    return state;   
}

Board& Game::getBoard() {
    return board;
}

std::string& Game::getMessage() {
    return message;
}

PieceType Game::getPieceType(Player* player) {
    return (player == player1.get()) ? PieceType::BLACK : PieceType::WHITE;
}

bool Game::placePiece(Pos pos, Player* player) {
    if (judge.isValidMove(board, pos)) {
        board.setPos(pos, getPieceType(player));
        return true;
    }
    return false;
}

void Game::changePlayer() {
    currentPlayer = (currentPlayer == player1.get()) ? player2.get() : player1.get();
}

void Game::setMessage(const std::string& msg) {
    message = msg;
}