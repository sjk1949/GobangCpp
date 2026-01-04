#pragma once

enum class PieceType {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

enum class GameResult
{
    NO_WINNER, //还没有分出胜负
    BLACK_WIN,
    WHITE_WIN,
    DRAW //平局
};

enum class PatternType
{
    FIVE,               // 连五
    OVERLINE,
    LIVE_FOUR,          // 活四
    SLEEP_FOUR,         // 冲四/眠四
    LIVE_THREE,         // 活三
    SLEEP_THREE,        // 眠三
    LIVE_TWO,           // 活二
    SLEEP_TWO,          // 眠二
    ONE,

    // 防守相关
    BLOCK_FOUR,         // 挡四
    BLOCK_THREE,
    BLOCK_TWO,
    INVALID
};

enum class ChessPatternType
{
    OVERLINE, // 在一条直线或斜线上，连续下成五个以上的棋型
    FIVE, // 五连
    LIVE_FOUR, // 指在一条直线或斜线上，由连续的四个字所构成的，无论对方怎样防守，只要再走一手棋将必定成为五连的棋型
    SLEEP_FOUR, // 在一条直线或斜线上，由四个同色子构成的，必须防守否则下一步立刻成为“五连”导致速胜的棋型。活四也是四之一。
    LIVE_THREE, // 在一条直线或斜线上，由三个子构成的，必须防守否则将成为“活四”导致速胜的棋型。
    NONE // 不属于以上任意棋型
};