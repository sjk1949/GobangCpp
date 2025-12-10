#pragma once

#include "Object.h"
#include <array>
#include "GameTypes.h"
#include "Pos.h"

/**
 * 这个类表示连子的结构，如三连，四连以及死活等
 */
class LineInfo : public Object
{
public:
    int length = 0;
    bool openEnds[2] = {false, false};
    Dir dir;
    std::string toString() const override {
        std::string str = "LineInfo@";
        str += "length: " + std::to_string(length) + "\n";
        str += "openEnds: " + std::to_string(openEnds[0]) + ", " + std::to_string(openEnds[1]) + "\n";
        str += "Direction: " + Pos::toPos(dir).toString();
        return str;
    }
};

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
    /**
     * @brief 检查给定位置连子数量最多的方向
     */
    LineInfo getLongestLine(Pos pos) const;
    /**
     * @brief 获得给定位置所有方向的连子情况
     */
    std::array<LineInfo, 4> getAllLines(Pos pos) const;
    /** 
     * @brief 检查给定位置在给定方向的连子数量，这里的方向包含两边
     * @param dir 一共四个方向HORIZONTAL, VAERTICAL, RIGHTUP, RIGHTDOWN
     */
    LineInfo checkLine(Pos pos, Dir dir) const;
    /**
     * @brief 检查给定位置在给定方向的连子数量
     * @param dir           只能在HERIZONTAL, VERTICAL, RIGHTUP, RIGHTDOWN四个方向中选择
     * @param isForward     以Pos坐标增大的方向为前方，说明是往前统计还是往后统计, 如果是true, 向前统计
     * @return              返回值length包含子本身，如果在该方向上被堵死，openEnds全为false，若没有，则全为true
     */
    LineInfo checkLineToDir(Pos pos, Dir dir, bool isForward) const;
    std::string toString() const override;

private:
    /* 棋盘数据用PieceType枚举存储，0代表空位，1代表黑子，2代表白子 */
    std::array<std::array<PieceType, BOARD_SIZE>, BOARD_SIZE> board;
    Board();
    /* 清空棋盘 */
    void clearBoard();
    /* 将Pos两边的连子情况合并 */
    LineInfo mergeLineInfo(LineInfo info1, LineInfo info2) const;
    std::string toStringRow(int row) const;
};