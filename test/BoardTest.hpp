#include <iostream>

#include "core/Board.hpp"

namespace Test
{
    class BoardTest
    {
    public:
        static void testLineToDir() {
            Board board = Board::createEmptyBoard();
            board.setPos(Pos(3, 3), PieceType::BLACK);
            board.setPos(Pos(3, 4), PieceType::BLACK);
            board.setPos(Pos(3, 5), PieceType::BLACK);
            board.setPos(Pos(3, 6), PieceType::BLACK);
            board.setPos(Pos(3, 7), PieceType::BLACK);
            board.setPos(Pos(3, 8), PieceType::WHITE);
            std::cout << board.toString() << std::endl;
            std::cout << board.checkLine(Pos(3, 4), Dir::HORIZONTAL).toString() << std::endl;
            std::cout << board.checkLine(Pos(3, 4), Dir::VERTICAL).toString() << std::endl;
        }
    };
};