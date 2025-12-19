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