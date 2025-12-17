#pragma once

#include <iostream>
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
    Game(std::unique_ptr<Player> player1, std::unique_ptr<Player> player2);
    GameState run();
    Board& getBoard();
    std::string& getMessage();

private:
    Board board;
    Judge judge;
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    Player* currentPlayer;
    GameState state;
    std::string message;
    

    /**
     * @brief player1执黑棋，player2执白棋
     */
    PieceType getPieceType(Player* player);

    bool placePiece(const Pos pos, Player* Player);
    /**
     * @brief 轮换正在下棋的玩家
     */
    void changePlayer();
    void setMessage(const std::string& msg);
};