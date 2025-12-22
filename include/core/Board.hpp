#pragma once

#include "utils/Object.hpp"

#include <array>
#include <unordered_map>
#include "core/GameTypes.hpp"
#include "core/Pos.hpp"

/**
 * 这个类代表一个棋盘
 */
class Board : public Object
{
public:
    /* 棋盘长度为15 */
    static const int BOARD_SIZE = 15;
    /* 获取空棋盘的工厂方法 */
    static Board createEmptyBoard();
    /* 将棋盘上的行号转化为坐标y值 */
    static int rowToPosY(int row);
    /* 判断给定坐标是否在棋盘上 */
    static bool isOnBoard(Pos pos);
    /* 访问棋盘数据 */
    PieceType getPos(Pos pos) const;
    /* 设置棋盘数据，返回值表示是否设置成功 */
    bool setPos(Pos pos, PieceType type);
    /* 返回该位置是否没有棋子 */
    bool isEmpty(Pos pos);
    
    static PieceType opponentOf(PieceType type);
    std::string toString() const override;
    std::string toString(const std::unordered_map<Pos, std::string, PosHash>* highlights) const;

private:
    /* 棋盘数据用PieceType枚举存储，0代表空位，1代表黑子，2代表白子 */
    std::array<std::array<PieceType, BOARD_SIZE>, BOARD_SIZE> board;
    Board();
    /* 清空棋盘 */
    void clearBoard();
    std::string pieceToString(const PieceType type) const;
    //std::string toStringRow(int row) const;
    std::string toStringRow(int row, const std::unordered_map<Pos, std::string, PosHash>* highlights = nullptr) const;
};

