#pragma once

#include "utils/Object.hpp"

#include <vector>
#include "core/Pos.hpp"
#include "core/Board.hpp"

enum class ChessPatternType
{
    OVERLINE, // 在一条直线或斜线上，连续下成五个以上的棋型
    FIVE, // 五连
    LIVE_FOUR, // 指在一条直线或斜线上，由连续的四个字所构成的，无论对方怎样防守，只要再走一手棋将必定成为五连的棋型
    SLEEP_FOUR, // 在一条直线或斜线上，由四个同色子构成的，必须防守否则下一步立刻成为“五连”导致速胜的棋型。活四也是四之一。
    LIVE_THREE, // 在一条直线或斜线上，由三个子构成的，必须防守否则将成为“活四”导致速胜的棋型。
    NONE // 不属于以上任意棋型
};

/**
 * @brief 代表一个棋型，一般来说maxDist不超过4，因为除了长连之外，其他棋型种类都需要在4格之内
 */
class ChessPattern : public Object
{
private:
    /**
     * @brief 返回在一条直线上的两个棋子之间的距离
     * @param 注意！函数默认两个棋子一定在一条直线上！
     */
    int pieceDist(const Pos pos1, const Pos pos2) const;
    bool compare(Pos pos1, Pos pos2);

public:
    std::vector<Pos> pieceList; // 棋型的位置一定在一条直线上, 且默认从一端到另一端顺序排列
    Board board; // 棋型和当时的棋局有关，同样的布局在不同的周边环境下意义可能会变
    ChessPatternType type = ChessPatternType::NONE;
    PieceType pieceType = PieceType::BLACK;
    
    ChessPattern(Board board);
    /**
     * @brief 加入一颗在棋盘上已有的棋子
     */
    ChessPattern& addPiece(Pos pos);
    /**
     * @brief 在棋盘上放置一颗棋子，并将它加入棋型
     */
    ChessPattern& placePiece(Pos pos);
    /**
     * @brief 延伸棋型，即加入与现在的棋型相连的同色子
     * 举几个例子，比如对于 
     *  处理前              处理后
     * ● ●●●▲●●● ●      ● ▲▲▲▲▲▲▲ ●
     *  ● ●▲● ●          ● ▲▲▲ ● 
     *  ● ●▲ ▲●●●       ● ▲▲ ▲▲▲▲
     */
    ChessPattern& expandPattern();

    /**
     * @brief 棋型两端的最大距离
     */
    int maxDist() const;
    /**
     * @brief 棋型的子数
     */
    int pieceNum() const;
    std::string toString() const override;
};