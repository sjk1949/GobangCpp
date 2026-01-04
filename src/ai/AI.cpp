#include "ai/AI.hpp"

#include <random>
#include <stdexcept>
#include "core/GameTypes.hpp"
#include "core/LineInfo.hpp"
#include "core/Judge.hpp"

AI::AI(AIStrategy strategy) : strategy(strategy) {}

Pos AI::calculateMove(const Board& board, PieceType aiPiece) {
    switch (strategy)
    {
    case AIStrategy::RANDOM:
        return randomMove(board, aiPiece);
    case AIStrategy::SCORE1:
        return calculateMoveV1(board, aiPiece);
    case AIStrategy::SCORE2:
        return calculateMoveV2(board, aiPiece);
    default:
        return Pos(-1, -1);
    }
}

Pos AI::calculateMoveV1(const Board& board, PieceType aiPiece) {
    return maxScoreMove(board, aiPiece);
}

Pos AI::calculateMoveV2(const Board& board, PieceType aiPiece) {
    return maxScoreMoveV2(board, aiPiece);
}

Pos AI::randomMove(const Board& board, PieceType aiPiece) {
    std::random_device rd;  // 使用硬件熵源获取随机种子
    std::mt19937 gen(rd()); // 使用Mersenne Twister引擎
    std::uniform_int_distribution<> distrib(0, Board::BOARD_SIZE - 1); // 生成[0,14]的整数
    
    Pos pos;
    Judge judge;
    do {
        pos = Pos(distrib(gen), distrib(gen));
    } while (!judge.isValidMove(board, pos, aiPiece));

    return pos;
}

Pos AI::maxScoreMove(const Board& board, PieceType aiPiece) {
    return genScoreMap(board, aiPiece).findMax();
}

Pos AI::maxScoreMoveV2(const Board& board, PieceType aiPiece) {
    return genScoreMapV2(board, aiPiece).findMax();
}

ScoreMap AI::genScoreMap(const Board& board, PieceType aiPiece) {
    ScoreMap scoreMap;
    Judge judge;
    scoreMap.initScoreMap();
    for (int x = 0; x < Board::BOARD_SIZE; x++) {
        for (int y = 0; y < Board::BOARD_SIZE; y++) {
            Pos pos(x, y);
            if (!judge.isValidMove(board, pos, aiPiece)) { //检查禁手，如果是禁手，不能落子
                scoreMap.setScore(pos, -1);
            } else {
                scoreMap.setScore(pos, getPosScore(board, pos, aiPiece) + scoreMap.getScore(pos));
            }
        }
    }
    return scoreMap;
}

ScoreMap AI::genScoreMapV2(const Board& board, PieceType aiPiece) {
    ScoreMap scoreMap;
    Judge judge;
    scoreMap.initScoreMap();
    for (int x = 0; x < Board::BOARD_SIZE; x++) {
        for (int y = 0; y < Board::BOARD_SIZE; y++) {
            Pos pos(x, y);
            if (!judge.isValidMove(board, pos, aiPiece)) { //检查禁手，如果是禁手，不能落子
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

int AI::getPosScore(const Board& board, Pos pos, PieceType aiPiece) {
    int score = 0;
    for (auto lineInfo : LineInfo::getAllLines(board, pos, aiPiece)) { //考虑自己走哪里能赢
        score += scorePattern(LineInfo::parsePatten(lineInfo));
    }
    for (auto lineInfo : LineInfo::getAllLines(board, pos, Board::opponentOf(aiPiece))) { //考虑如何阻止对方赢
        score += 0.9 * scorePattern(LineInfo::parsePatten(lineInfo)); 
    }
    return score;
}

int AI::getPosScoreV2(const Board& board, Pos pos, PieceType aiPiece) {
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