#pragma once

#include <iostream>
#include <array>
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
            Judge judge;
            Board board = Board::createEmptyBoard();
            board.setPos(Pos(5, 6), PieceType::BLACK);
            board.setPos(Pos(6, 6), PieceType::BLACK);
            board.setPos(Pos(7, 6), PieceType::BLACK);
            board.setPos(Pos(5, 5), PieceType::BLACK);
            board.setPos(Pos(8, 8), PieceType::BLACK);
            board.setPos(Pos(6, 7), PieceType::BLACK);
            board.setPos(Pos(6, 8), PieceType::BLACK);
            board.setPos(Pos(6, 9), PieceType::BLACK);
            board.setPos(Pos(6, 10), PieceType::BLACK);
            board.setPos(Pos(6, 11), PieceType::BLACK);
            std::cout << board.toString() << std::endl;
            for (auto pattern : judge.analyse(board, Pos(6, 6), PieceType::BLACK)) {
                for (auto type : pattern) {
                    std::cout << judge.chessPatternTypeToString(type) << std::endl;
                }
                
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
            for (auto pattern : judge.analyse(board, Pos(8, 6), PieceType::BLACK)) {
                for (auto type : pattern) {
                    std::cout << judge.chessPatternTypeToString(type) << std::endl;
                }
                
            }
            board = Board::createEmptyBoard();
            board.setPos(Pos(5, 6), PieceType::BLACK);
            board.setPos(Pos(6, 6), PieceType::BLACK);
            board.setPos(Pos(8, 6), PieceType::BLACK);
            board.setPos(Pos(9, 6), PieceType::BLACK);
            board.setPos(Pos(11, 6), PieceType::BLACK);
            board.setPos(Pos(12, 6), PieceType::BLACK);
            board.setPos(Pos(8, 7), PieceType::BLACK);
            board.setPos(Pos(8, 8), PieceType::BLACK);
            board.setPos(Pos(8, 9), PieceType::BLACK);
            board.setPos(Pos(9, 7), PieceType::BLACK);
            board.setPos(Pos(10, 8), PieceType::BLACK);
            board.setPos(Pos(11, 9), PieceType::BLACK);
            board.setPos(Pos(12, 10), PieceType::BLACK);
            std::cout << board.toString() << std::endl;
            for (auto pattern : judge.analyse(board, Pos(8, 6), PieceType::BLACK)) {
                for (auto type : pattern) {
                    std::cout << judge.chessPatternTypeToString(type) << std::endl;
                }
            }
        }

        /**
         * @brief 测试一般的禁手分析
         */
        static void testCheckForbidden() {
            Judge judge;
            Board board = Board::createEmptyBoard();
            board.setPos(Pos(5, 6), PieceType::BLACK);
            board.setPos(Pos(7, 6), PieceType::BLACK);
            board.setPos(Pos(9, 6), PieceType::BLACK);
            board.setPos(Pos(11, 6), PieceType::BLACK);
            Pos pos(8, 6);
            std::unordered_map<Pos, std::string, PosHash> highlights;
            highlights[pos] = " ▲ ";
            std::cout << board.toString(&highlights) << std::endl;
            std::cout << pos.toString() << " forbidden type: " << judge.forbiddenTypeToString(judge.checkForbidden(board, pos, PieceType::BLACK)) << std::endl;

            board = Board::createEmptyBoard();
            board.setPos(Pos(2, 2), PieceType::BLACK);
            board.setPos(Pos(4, 2), PieceType::BLACK);
            board.setPos(Pos(4, 1), PieceType::BLACK);
            board.setPos(Pos(1, 4), PieceType::BLACK);
            pos = {3, 2};
            highlights.clear();
            highlights[pos] = " ▲ ";
            std::cout << board.toString(&highlights) << std::endl;
            std::cout << pos.toString() << " forbidden type: " << judge.forbiddenTypeToString(judge.checkForbidden(board, pos, PieceType::BLACK)) << std::endl;

            board = Board::createEmptyBoard();
            board.setPos(Pos(5, 4), PieceType::BLACK);
            board.setPos(Pos(5, 5), PieceType::BLACK);
            board.setPos(Pos(5, 6), PieceType::BLACK);
            board.setPos(Pos(4, 7), PieceType::BLACK);
            board.setPos(Pos(5, 8), PieceType::BLACK);
            board.setPos(Pos(5, 9), PieceType::BLACK);
            pos = {5, 7};
            highlights.clear();
            highlights[pos] = " ▲ ";
            std::cout << board.toString(&highlights) << std::endl;
            std::cout << pos.toString() << " forbidden type: " << judge.forbiddenTypeToString(judge.checkForbidden(board, pos, PieceType::BLACK)) << std::endl;

            board = Board::createEmptyBoard();
            board.setPos(Pos(5, 4), PieceType::BLACK);
            board.setPos(Pos(5, 5), PieceType::BLACK);
            board.setPos(Pos(5, 6), PieceType::BLACK);
            board.setPos(Pos(4, 7), PieceType::BLACK);
            board.setPos(Pos(6, 7), PieceType::BLACK);
            board.setPos(Pos(7, 7), PieceType::BLACK);
            board.setPos(Pos(8, 7), PieceType::BLACK);
            board.setPos(Pos(5, 8), PieceType::BLACK);
            board.setPos(Pos(5, 9), PieceType::BLACK);
            pos = {5, 7};
            highlights.clear();
            highlights[pos] = " ▲ ";
            std::cout << board.toString(&highlights) << std::endl;
            std::cout << pos.toString() << " forbidden type: " << judge.forbiddenTypeToString(judge.checkForbidden(board, pos, PieceType::BLACK)) << std::endl;

            board = Board::createEmptyBoard();
            board.setPos(Pos(5, 2), PieceType::WHITE);
            board.setPos(Pos(5, 4), PieceType::BLACK);
            board.setPos(Pos(5, 6), PieceType::BLACK);
            board.setPos(Pos(5, 8), PieceType::WHITE);
            board.setPos(Pos(6, 5), PieceType::BLACK);
            board.setPos(Pos(7, 5), PieceType::BLACK);
            pos = {5, 5};
            highlights.clear();
            highlights[pos] = " ▲ ";
            std::cout << board.toString(&highlights) << std::endl;
            std::cout << pos.toString() << " forbidden type: " << judge.forbiddenTypeToString(judge.checkForbidden(board, pos, PieceType::BLACK)) << std::endl;
        }

        /**
         * @brief 测试复杂递归禁手
         */
        static void testRecursiveCheckForbidden() {
            // @todo
            Judge judge;
            Board board = Board::createEmptyBoard();
            board.setPos(Pos(6, 5), PieceType::BLACK);
            board.setPos(Pos(7, 6), PieceType::BLACK);
            board.setPos(Pos(8, 6), PieceType::BLACK);
            board.setPos(Pos(8, 8), PieceType::BLACK);
            board.setPos(Pos(9, 7), PieceType::BLACK);
            board.setPos(Pos(10, 7), PieceType::BLACK);
            board.setPos(Pos(11, 6), PieceType::BLACK);
            board.setPos(Pos(11, 8), PieceType::BLACK);
            board.setPos(Pos(13, 7), PieceType::WHITE);
            board.setPos(Pos(10, 9), PieceType::WHITE);
            Pos pos(11, 7);
            std::unordered_map<Pos, std::string, PosHash> highlights;
            highlights[pos] = " ▲ ";
            std::cout << board.toString(&highlights) << std::endl;
            std::cout << pos.toString() << " forbidden type: " << judge.forbiddenTypeToString(judge.checkForbidden(board, pos, PieceType::BLACK)) << std::endl;

            board = Board::createEmptyBoard();
            board.setPos(Pos(3, 4), PieceType::BLACK);
            board.setPos(Pos(4, 4), PieceType::BLACK);
            board.setPos(Pos(4, 5), PieceType::BLACK);
            board.setPos(Pos(6, 3), PieceType::BLACK);
            board.setPos(Pos(6, 5), PieceType::BLACK);
            board.setPos(Pos(7, 6), PieceType::BLACK);
            board.setPos(Pos(8, 6), PieceType::BLACK);
            board.setPos(Pos(8, 8), PieceType::BLACK);
            board.setPos(Pos(9, 7), PieceType::BLACK);
            board.setPos(Pos(10, 7), PieceType::BLACK);
            board.setPos(Pos(11, 6), PieceType::BLACK);
            board.setPos(Pos(11, 8), PieceType::BLACK);
            board.setPos(Pos(13, 7), PieceType::WHITE);
            board.setPos(Pos(10, 9), PieceType::WHITE);
            pos = {11, 7};
            highlights.clear();
            highlights[pos] = " ▲ ";
            std::cout << board.toString(&highlights) << std::endl;
            std::cout << pos.toString() << " forbidden type: " << judge.forbiddenTypeToString(judge.checkForbidden(board, pos, PieceType::BLACK)) << std::endl;
        }
    };
} // Test

