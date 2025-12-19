#pragma once

#include "utils/Object.hpp"

#include <string>

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

    GameConfig(std::string player1Name = "Player1", std::string player2Name = "Player2",
         bool player1IsAI = false, bool player2IsAI = false) : 
         player1Name(player1Name), player1IsAI(player1IsAI), player2Name(player2Name), player2IsAI(player2IsAI) {};
};