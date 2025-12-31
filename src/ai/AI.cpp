#include "ai/AI.hpp"

#include <random>
#include <stdexcept>
#include "core/GameTypes.hpp"
#include "core/LineInfo.hpp"
#include "core/ChessPattern.hpp"
#include "core/Judge.hpp"

AI::AI(AIStrategy strategy) : strategy(strategy) {}

Pos AI::calculateMove(Board& board, PieceType aiPiece) {
    switch (strategy)
    {
    case AIStrategy::RANDOM:
        return randomMove(board);
    case AIStrategy::SCORE1:
        return calculateMoveV1(board, aiPiece);
    case AIStrategy::SCORE2:
        return calculateMoveV2(board, aiPiece);
    default:
        return Pos(-1, -1);
    }
}

Pos AI::calculateMoveV1(Board& board, PieceType aiPiece) {
    // @todo 根据棋盘分数图取最大值算出最佳位置
    return maxScoreMove(board, aiPiece);
}

Pos AI::calculateMoveV2(Board& board, PieceType aiPiece) {
    // @todo 根据棋盘分数图取最大值算出最佳位置
    return maxScoreMoveV2(board, aiPiece);
}

Pos AI::randomMove(Board& board) {
    std::random_device rd;  // 使用硬件熵源获取随机种子
    std::mt19937 gen(rd()); // 使用Mersenne Twister引擎
    std::uniform_int_distribution<> distrib(0, Board::BOARD_SIZE - 1); // 生成[0,14]的整数
    
    Pos pos;
    do {
        pos = Pos(distrib(gen), distrib(gen));
    } while (!board.isEmpty(pos));

    return pos;
}

Pos AI::maxScoreMove(Board& board, PieceType aiPiece) {
    return genScoreMap(board, aiPiece).findMax();
}

Pos AI::maxScoreMoveV2(Board& board, PieceType aiPiece) {
    return genScoreMapV2(board, aiPiece).findMax();
}

ScoreMap AI::genScoreMap(Board& board, PieceType aiPiece) {
    ScoreMap scoreMap;
    scoreMap.initScoreMap();
    for (int x = 0; x < Board::BOARD_SIZE; x++) {
        for (int y = 0; y < Board::BOARD_SIZE; y++) {
            Pos pos(x, y);
            if (!board.isEmpty(pos)) { //如果位置已经有棋子了，不能重复落子
                scoreMap.setScore(pos, -1);
            } else {
                scoreMap.setScore(pos, getPosScore(board, pos, aiPiece) + scoreMap.getScore(pos));
            }
        }
    }
    return scoreMap;
}

ScoreMap AI::genScoreMapV2(Board& board, PieceType aiPiece) {
    ScoreMap scoreMap;
    scoreMap.initScoreMap();
    for (int x = 0; x < Board::BOARD_SIZE; x++) {
        for (int y = 0; y < Board::BOARD_SIZE; y++) {
            Pos pos(x, y);
            if (!board.isEmpty(pos)) { //如果位置已经有棋子了，不能重复落子
                scoreMap.setScore(pos, -1);
            } else {
                scoreMap.setScore(pos, getPosScoreV2(board, pos, aiPiece) + scoreMap.getScore(pos));
            }
        }
    }
    return scoreMap;
}


int AI::scorePattern(const PatternType pattern) {
    switch (pattern)
    {
    case PatternType::FIVE:
        return 10000;
    case PatternType::OVERLINE:
        return 10000;
    case PatternType::LIVE_FOUR:
        return 3000;
    case PatternType::SLEEP_FOUR:
        return 600;
    case PatternType::BLOCK_FOUR:
        return 0;
    case PatternType::LIVE_THREE:
        return 500;
    case PatternType::SLEEP_THREE:
        return 300;
    case PatternType::BLOCK_THREE:
        return 0;
    case PatternType::LIVE_TWO:
        return 100;
    case PatternType::SLEEP_TWO:
        return 20;
    case PatternType::BLOCK_TWO:
        return 0;
    case PatternType::ONE:
        return 1;
    default:
        throw std::invalid_argument("Unknow pattern");
    }
}

int AI::getPosScore(Board& board, Pos pos, PieceType aiPiece) {
    int score = 0;
    for (auto lineInfo : LineInfo::getAllLines(board, pos, aiPiece)) { //考虑自己走哪里能赢
        score += scorePattern(LineInfo::parsePatten(lineInfo));
    }
    for (auto lineInfo : LineInfo::getAllLines(board, pos, Board::opponentOf(aiPiece))) { //考虑如何阻止对方赢
        score += 0.9 * scorePattern(LineInfo::parsePatten(lineInfo)); 
    }
    return score;
}

int AI::getPosScoreV2(Board& board, Pos pos, PieceType aiPiece) {
    Judge judge;
    int score = 0;
    for (auto pattern : judge.analyse(board, pos, aiPiece)) { //考虑自己走哪里能赢
        for (auto type : pattern) {
            score += scorePattern(type);
        }
    }
    for (auto pattern : judge.analyse(board, pos, Board::opponentOf(aiPiece))) { //考虑如何阻止对方赢
        for (auto type : pattern) {
            score += 0.9 * scorePattern(type);
        }
    }
    return score;
}

int AI::scorePattern(const ChessPatternType pattern) {
    switch (pattern)
    {
    case ChessPatternType::FIVE:
        return 10000;
    case ChessPatternType::OVERLINE:
        return 10000;
    case ChessPatternType::LIVE_FOUR:
        return 3000;
    case ChessPatternType::SLEEP_FOUR:
        return 600;
    case ChessPatternType::LIVE_THREE:
        return 500;
    case ChessPatternType::NONE:
        return 0;
    default:
        throw std::invalid_argument("Unknow pattern");
    }
}