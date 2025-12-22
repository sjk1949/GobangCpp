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
            board.setPos(Pos(5, 5), PieceType::BLACK);
            board.setPos(Pos(5, 6), PieceType::BLACK);
            board.setPos(Pos(5, 7), PieceType::BLACK);
            board.setPos(Pos(5, 9), PieceType::BLACK);
            board.setPos(Pos(5, 12), PieceType::BLACK);
            ChessPattern pattern(board);
            pattern.addPiece(Pos(5, 9));
            pattern.addPiece(Pos(5, 7));
            pattern.addPiece(Pos(5, 5));
            pattern.addPiece(Pos(5, 5));
            std::cout << pattern.toString() << std::endl;
        }
    };
} // Test

