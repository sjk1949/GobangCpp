#include "core/Game.hpp"

#include <chrono>
#include "core/Board.hpp"
#include "player/HumanPlayer.hpp"
#include "player/AIPlayer.hpp"

/*
Game::Game(std::unique_ptr<Player> player1, std::unique_ptr<Player> player2) : board(Board::createEmptyBoard()), judge(Judge()) {
    this->player1 = std::move(player1);
    this->player2 = std::move(player2);
    currentPlayer = this->player1.get();
    state = GameState::PLAYING;
    startTurnTime = std::chrono::steady_clock::now();
}
*/

Game::Game(GameConfig config) : board(Board::createEmptyBoard()), judge(Judge()) {
    if (config.player1IsAI) {
        player1 = std::make_unique<AIPlayer>(config.player1Name, config.player1Strategy);
    } else {
        player1 = std::make_unique<HumanPlayer>(config.player1Name, config.player1Strategy);
    }
    if (config.player2IsAI) {
        player2 = std::make_unique<AIPlayer>(config.player2Name, config.player2Strategy);
    } else {
        player2 = std::make_unique<HumanPlayer>(config.player2Name, config.player2Strategy);
    }
    useTimeLimit = config.useTimeLimit;
    currentPlayer = this->player1.get();
    state = GameState::PLAYING;
    startTurnTime = std::chrono::steady_clock::now();
}

void Game::handleInput(std::unique_ptr<GameCommand> command) {
    if (state == GameState::PLAYING) {
        currentPlayer->push(std::move(command));
    } else { // 如果游戏结束，输入任意指令视为退出
        if (command) {
            quit();
        }
    }
    
}

void Game::update() {
    if (state != GameState::PLAYING) {
        return;
    }
    if (hasTimeLimit() && checkTimeout()) {
        setMessage("时间到，自动认输！");
        state = (getPieceType(currentPlayer) == PieceType::BLACK) ? GameState::WHITE_WIN : GameState::BLACK_WIN;
        return;
    }
    std::unique_ptr<GameCommand> command = currentPlayer -> getCommand(board, getPieceType(currentPlayer));
    if (command == nullptr) {
        return;
    }
    command->execute(*this);
}

void Game::placePieceAndCheck(Pos pos) {
    if (placePiece(pos, currentPlayer)) {
        history.addMove({pos, getPieceType(currentPlayer)});
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
    }
}

void Game::undoLastMove() {
    if (!history.canUndo()) {
        setMessage("不能撤销！");
        return;
    }
    Move move = history.undoLastMove();
    board.setPos(move.pos, PieceType::EMPTY);
    changePlayer();
    if (currentPlayer->isAI && history.canUndo()) { // 如果悔棋后对方是AI，且能撤一步，需要再撤一步
        Move move = history.undoLastMove();
        board.setPos(move.pos, PieceType::EMPTY);
        changePlayer();
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

const bool Game::hasTimeLimit() const {
    return useTimeLimit;
}

bool Game::placePiece(Pos pos, Player* player) {
    return placePiece(board, pos, getPieceType(player));
}

bool Game::placePiece(const Board& board, const Pos pos, PieceType type) {
    switch (judge.checkValidMove(board, pos, type))
    {
    case ForbiddenType::NONE:
        this->board.setPos(pos, type); //如果没有违规或禁手，落子
        return true;
    case ForbiddenType::OUT_OF_BOUND:
        setMessage("落子超出棋盘边界！");
        break;
    case ForbiddenType::PIECE_ALREADY_EXIST:
        setMessage("不能在其他棋子上落子！");
        break;
    case ForbiddenType::OVERLINE:
        setMessage("黑棋长连禁手");
        break;
    case ForbiddenType::DOUBLE_FOUR:
        setMessage("黑棋四四禁手");
        break;
    case ForbiddenType::DOUBLE_THREE:
        setMessage("黑棋三三禁手");
        break;
    default:
        setMessage("触发未知错误");
        break;
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