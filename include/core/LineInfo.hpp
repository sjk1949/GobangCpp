#pragma once

#include "utils/Object.hpp"

#include <array>
#include <vector>
#include "core/GameTypes.hpp"
#include "core/Board.hpp"
#include "core/Pos.hpp"

/**
 * 这个类表示连子的结构，如三连，四连以及死活等
 */
class LineInfo : public Object
{
public:
    int length = 0;
    bool openEnds[2] = {false, false};
    Dir dir;
    std::vector<Pos> extension; // 两端可用的拓展点（不能出棋盘，不能有棋子阻挡，不考虑禁手)
    /**
     * @brief 检查给定位置连子数量最多的方向
     */
    static LineInfo getLongestLine(const Board& board, Pos pos);
    /**
     * @brief 检查如果给定位置是给定类型，连子数量最多的方向
     */
    static LineInfo getLongestLine(const Board& board, Pos pos, PieceType type);
    /**
     * @brief 获得给定位置所有方向的连子情况
     */
    static std::array<LineInfo, 4> getAllLines(const Board& board, Pos pos);
    /**
     * @brief 获得如果给定位置是给定类型，所有方向的连子情况
     */
    static std::array<LineInfo, 4> getAllLines(const Board& board, Pos pos, PieceType type);
    /** 
     * @brief 检查给定位置在给定方向的连子数量，这里的方向包含两边
     * @param dir 一共四个方向HORIZONTAL, VAERTICAL, RIGHTUP, RIGHTDOWN
     */
    static LineInfo checkLine(const Board& board, Pos pos, Dir dir);
    /** 
     * @brief 检查如果给定位置是给定类型棋子，在给定方向的连子数量，这里的方向包含两边
     * @param dir 一共四个方向HORIZONTAL, VAERTICAL, RIGHTUP, RIGHTDOWN
     */
    static LineInfo checkLine(const Board& board, Pos pos, Dir dir, PieceType type);
    /**
     * @brief 检查给定位置在给定方向的连子数量
     * @param dir           只能在HERIZONTAL, VERTICAL, RIGHTUP, RIGHTDOWN四个方向中选择
     * @param isForward     以Pos坐标增大的方向为前方，说明是往前统计还是往后统计, 如果是true, 向前统计
     * @return              返回值length包含子本身，如果在该方向上被堵死，openEnds全为false，若没有，则全为true
     */
    static LineInfo checkLineToDir(const Board& board, Pos pos, Dir dir, bool isForward);
    /**
     * @brief 检查给定位置如果是给定棋子类型，则在给定方向的连子数量
     * @param dir           只能在HERIZONTAL, VERTICAL, RIGHTUP, RIGHTDOWN四个方向中选择
     * @param isForward     以Pos坐标增大的方向为前方，说明是往前统计还是往后统计, 如果是true, 向前统计
     * @param type          仅支持BLACK, WHITE两种类型
     * @return              返回值length包含子本身，如果在该方向上被堵死，openEnds全为false，若没有，则全为true
     */
    static LineInfo checkLineToDir(const Board& board, Pos pos, Dir dir, bool isForward, PieceType type);
    static PatternType parsePatten(LineInfo lineInfo);
    std::string toString() const override;

private:
    /* 将Pos两边的连子情况合并 */
    static LineInfo mergeLineInfo(LineInfo info1, LineInfo info2);
};