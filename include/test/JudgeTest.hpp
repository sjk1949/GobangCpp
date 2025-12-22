#pragma once

#include <iostream>
#include "core/ChessPattern.hpp"
#include "core/Board.hpp"

namespace Test
{
    class JudgeTest
    {
    private:
    public:
        static void testChessPattern() {
            Board board = Board::createEmptyBoard();
            board.setPos(Pos(1, 1), PieceType::BLACK);
            board.setPos(Pos(1, 2), PieceType::BLACK);
            board.setPos(Pos(1, 3), PieceType::BLACK);
            ChessPattern pattern(board);
            pattern.addPiece(Pos(1, 1));
            pattern.addPiece(Pos(1, 3));
            pattern.addPiece(Pos(1, 2));
            std::cout << pattern.toString() << std::endl;
        }
    };
} // Test

