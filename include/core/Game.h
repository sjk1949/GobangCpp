#pragma once

#include <chrono>
#include <memory>

#include "core/Board.h"
#include "core/Judge.h"
#include "player/Player.h"

enum class GameState
{
    PLAYING,
    BLACK_WIN,
    WHITE_WIN,
    DRAW,
    QUIT
};

class Game
{
public:
    static const int TURN_TIME_LIMIT = 15; // 每回合时间限制，单位为s
    
    Game(std::unique_ptr<Player> player1, std::unique_ptr<Player> player2);
    void handleInput(InputResult result);
    void update();
    const Board& getBoard() const;
    const std::string& getMessage() const;
    const GameState& getGameState() const;
    PieceType getCurrentPieceType() const;
    int getRemainingTime() const;

private:
    Board board;
    Judge judge;
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    Player* currentPlayer;
    std::chrono::steady_clock::time_point startTurnTime;
    GameState state;
    std::string message;
    

    /**
     * @brief player1执黑棋，player2执白棋
     */
    PieceType getPieceType(Player* player) const;

    bool placePiece(const Pos pos, Player* Player);
    /**
     * @brief 轮换正在下棋的玩家
     */
    void changePlayer();
    bool checkTimeout() const;
    void setMessage(const std::string& msg);
};