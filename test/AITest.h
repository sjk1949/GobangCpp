#include <iostream>

#include "..\src\Board.h"
#include "..\src\AI.h"
#include "..\src\ScoreMap.h"

namespace Test
{
    class AITest
    {
    public:
        static void testRandomAI() {
            Board board = Board::createEmptyBoard();
            AI ai;
            for (int i = 0; i < 10; i++) {
                board.setPos(ai.calculateMove(board, PieceType::BLACK), PieceType::BLACK);
                std::cout << board.toString() << std::endl;
            }
        }

        static void testScoreMap() {
            ScoreMap scoreMap = ScoreMap::createEmptyScoreMap();
            scoreMap.initScoreMap();
            std::cout << scoreMap.toString() << std::endl;
        }
    };
};
