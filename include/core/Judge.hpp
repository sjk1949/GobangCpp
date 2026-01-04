#pragma once

#include <map>
#include "core/Pos.hpp"
#include "core/Board.hpp"
#include "core/GameTypes.hpp"
#include "core/LineInfo.hpp"

/**
 * 禁手包括三三，三四，长连禁手
 */
enum class ForbiddenType
{
    NONE, // 无禁手
    OVERLINE, // 长连禁手：当黑棋走一步棋，形成长连棋型，则此点为“禁手”
    DOUBLE_FOUR, // 当黑棋走一步棋，同时形成两个或两个以上的“四”且没有形成“五连”时，那一步棋就是黑棋禁手。
    DOUBLE_THREE, // 当黑棋走一步棋，同时形成两个或两个以上的“活三”且没有形成“五连”时，那一步棋就是黑棋禁手。

    //一般禁止类型
    OUT_OF_BOUND, // 超出棋盘边界
    PIECE_ALREADY_EXIST // 已经存在棋子
};

class Judge
{
private:
    
public:
    Judge() = default;
    ForbiddenType checkValidMove(const Board& board, const Pos pos, PieceType type);
    /* 判断在给定Pos处落子是否符合规则，如果符合，返回true */
    bool isValidMove(const Board& board, const Pos pos, PieceType type);
    /**
     * @brief 根据上一个落子的位置检查当前棋局是否已经分出胜负
     * @return  NO_WINNER说明还未分出胜负
     */
    GameResult ckeckWin(const Board& board, Pos lastDrop);
    /**
     * @brief 检测黑棋下在给定的位置会不会形成禁手
     * @param board 这里的棋盘是已经落上子之后的棋盘
     * @return 返回禁手类型，如果没有禁手，返回ForbiddenType::NONE
     */
    ForbiddenType checkForbidden(const Board& board, Pos pos, PieceType type);
    bool isForbidden(const Board& board, Pos pos, PieceType type);
    std::array<std::vector<ChessPatternType>, 4> analyse(const Board& board, Pos pos, PieceType type);
    std::vector<ChessPatternType> analyse(const Board& board, LineInfo info, PieceType type);
    bool isLiveThree(const Board& board, LineInfo info, PieceType type);
    /**
     * @brief 检查一个棋型在可扩展位置落一子后能否变成活四，如果是，说明这个棋型是活三
     */
    bool canBecomeLiveFour(const Board& board, LineInfo info, PieceType type);
    bool isLiveFour(const Board& board, LineInfo info, PieceType type);
    bool isFour(const Board& board, LineInfo info, PieceType type);
    /**
     * @brief 根据给定的LineInfo，识别出四的类型和数量，比如EBEBBBEBE是两个冲四
     */
    std::vector<ChessPatternType> analyseFour(const Board& board, LineInfo info, PieceType type);
    bool canBecomeFive(const Board& board, LineInfo info, PieceType type);
    /**
     * @brief 检查一个棋型有多少个可以成五的拓展点位
     * @return 可以成五的点位数量
     */
    int canBecomeFiveNum(const Board& board, LineInfo info, PieceType type);
    bool isFive(const Board& board, LineInfo info, PieceType type);
    bool isOverLine(const Board& board, LineInfo info, PieceType type);
    std::string chessPatternTypeToString(ChessPatternType type);
    std::string forbiddenTypeToString(ForbiddenType type);

private:
    /**
     * @brief 统计一个落点四个方向棋型信息所含的不同棋型数量
     */
    std::map<ChessPatternType, int> countPattern(std::array<std::vector<ChessPatternType>, 4> patternList);
};
