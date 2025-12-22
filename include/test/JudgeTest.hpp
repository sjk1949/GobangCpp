#pragma once

#include <iostream>
#include <array>
#include "core/ChessPattern.hpp"
#include "core/LineInfo.hpp"
#include "core/Board.hpp"

namespace Test
{
    class JudgeTest
    {
    private:
    public:
        static void testLineInfo() {
            Board board = Board::createEmptyBoard();
            board.setPos(Pos(0, 0), PieceType::BLACK);
            board.setPos(Pos(5, 5), PieceType::BLACK);
            board.setPos(Pos(5, 6), PieceType::BLACK);
            board.setPos(Pos(5, 7), PieceType::BLACK);
            board.setPos(Pos(5, 8), PieceType::WHITE);
            board.setPos(Pos(5, 11), PieceType::BLACK);
            board.setPos(Pos(5, 12), PieceType::BLACK);
            std::cout << board.toString() << std::endl;
            std::array<LineInfo, 4> lineInfos;
            lineInfos = LineInfo::getAllLines(board, Pos(5, 7));
            for (auto line : lineInfos) {
                std::cout << line.toString() << std::endl;
            }
            lineInfos = LineInfo::getAllLines(board, Pos(0, 0));
            for (auto line : lineInfos) {
                std::cout << line.toString() << std::endl;
            }
        }

        static void testChessPatternTypeWithoutForbidden() {
            Board board = Board::createEmptyBoard();
            board.setPos(Pos(5, 6), PieceType::BLACK);
            board.setPos(Pos(6, 6), PieceType::BLACK);
            board.setPos(Pos(7, 6), PieceType::BLACK);
            board.setPos(Pos(5, 5), PieceType::BLACK);
            board.setPos(Pos(8, 8), PieceType::BLACK);
            board.setPos(Pos(6, 7), PieceType::BLACK);
            std::cout << board.toString() << std::endl;
            Judge judge;
            for (auto type : judge.analyse(board, Pos(6, 6), PieceType::BLACK)) {
                std::cout << judge.chessPatternTypeToString(type) << std::endl;
            }
            board = Board::createEmptyBoard();
            board.setPos(Pos(5, 6), PieceType::BLACK);
            board.setPos(Pos(7, 6), PieceType::BLACK);
            board.setPos(Pos(8, 6), PieceType::BLACK);
            board.setPos(Pos(9, 6), PieceType::BLACK);
            board.setPos(Pos(11, 6), PieceType::BLACK);
            board.setPos(Pos(8, 7), PieceType::BLACK);
            board.setPos(Pos(8, 9), PieceType::BLACK);
            board.setPos(Pos(8, 10), PieceType::BLACK);
            std::cout << board.toString() << std::endl;
            for (auto type : judge.analyse(board, Pos(8, 6), PieceType::BLACK)) {
                std::cout << judge.chessPatternTypeToString(type) << std::endl;
            }
        }
    };
} // Test

