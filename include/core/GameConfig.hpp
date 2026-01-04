#pragma once

#include "utils/Object.hpp"

#include <string>
#include "ai/AI.hpp"

/**
 * @brief 这个类包含了一局游戏需要的所有设置
 */
class GameConfig : public Object
{
public:
    std::string player1Name;
    std::string player2Name;
    bool player1IsAI;
    bool player2IsAI;
    AIStrategy player1Strategy;
    AIStrategy player2Strategy;
    bool useTimeLimit;
    bool allowUndo;

    GameConfig(std::string player1Name = "Player1", std::string player2Name = "Player2"
        , bool player1IsAI = false, bool player2IsAI = false
        , AIStrategy player1Strategy = AIStrategy::SCORE1, AIStrategy player2Strategy = AIStrategy::SCORE1
        , bool useTimeLimit = false, bool allowUndo = true) 
         : player1Name(player1Name), player1IsAI(player1IsAI), player1Strategy(player1Strategy)
         , player2Name(player2Name), player2IsAI(player2IsAI), player2Strategy(player2Strategy)
         , useTimeLimit(useTimeLimit), allowUndo(allowUndo) {};
};