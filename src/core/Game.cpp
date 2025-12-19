#include "core/Game.h"

#include <chrono>
#include "core/Board.h"
#include "player/HumanPlayer.h"
#include "player/AIPlayer.h"

Game::Game(std::unique_ptr<Player> player1, std::unique_ptr<Player> player2) : board(Board::createEmptyBoard()), judge(Judge()) {
    this->player1 = std::move(player1);
    this->player2 = std::move(player2);
    currentPlayer = this->player1.get();
    state = GameState::PLAYING;
    startTurnTime = std::chrono::steady_clock::now();
}

void Game::handleInput(InputResult result) {
    currentPlayer->push(result);
}

void Game::update() {
    if (checkTimeout()) {
        setMessage("时间到，自动认输！");
        state = (getPieceType(currentPlayer) == PieceType::BLACK) ? GameState::WHITE_WIN : GameState::BLACK_WIN;
        return;
    }
    InputResult result = currentPlayer -> getCommand(board, getPieceType(currentPlayer));
    switch (result.command)
    {
    case InputCommand::NONE: // 如果没有接收到指令
        return;
    case InputCommand::QUIT:
        quit();
        break;
    case InputCommand::PLACE_PIECE:
        placePieceAndCheck(result.pos);
        break;
    case InputCommand::INVALID:
        recievedInvalidCommand();
        break;
    default:
        break;
    }
}

void Game::placePieceAndCheck(Pos pos) {
    if (placePiece(pos, currentPlayer)) {
        switch (judge.ckeckWin(board, pos))
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
        setMessage("");
    } else {
        setMessage("不能在该处落子！");
    }
}

void Game::quit() {
    state = GameState::QUIT;
}

void Game::recievedInvalidCommand() {
    setMessage("非法输入");
}

const Board& Game::getBoard() const {
    return board;
}

const std::string& Game::getMessage() const {
    return message;
}

const GameState& Game::getGameState() const {
    return state;
}

PieceType Game::getPieceType(Player* player) const {
    return (player == player1.get()) ? PieceType::BLACK : PieceType::WHITE;
}

PieceType Game::getCurrentPieceType() const {
    return getPieceType(currentPlayer);
}

int Game::getRemainingTime() const {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTurnTime).count();
    int remaining = TURN_TIME_LIMIT - static_cast<int>(elapsed);
    return (remaining > 0) ? remaining : 0;
}

bool Game::checkTimeout() const {
    return getRemainingTime() <= 0;
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
    startTurnTime = std::chrono::steady_clock::now();
}

void Game::setMessage(const std::string& msg) {
    message = msg;
}