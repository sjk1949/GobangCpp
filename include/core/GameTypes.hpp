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