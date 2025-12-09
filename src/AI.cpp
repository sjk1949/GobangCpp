#include "AI.h"

#include <random>

Pos AI::calculateMove(Board& board, PieceType aiPiece) {
    // @todo 根据棋盘分数图取最大值算出最佳位置
    return randomMove(board);
}

Pos AI::randomMove(Board& board) {
    std::random_device rd;  // 使用硬件熵源获取随机种子
    std::mt19937 gen(rd()); // 使用Mersenne Twister引擎
    std::uniform_int_distribution<> distrib(0, Board::BOARD_SIZE); // 生成[1,100]的整数
    
    Pos pos;
    do {
        pos = Pos(distrib(gen), distrib(gen));
    } while (!board.isEmpty(pos));

    return pos;
}