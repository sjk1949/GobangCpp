#include <array>
#include <sstream>
#include <iomanip>

#include "core/Board.hpp"
#include "core/GameTypes.hpp"

Board::Board() {
    clearBoard();
}

Board Board::createEmptyBoard() {
    return Board();
}

int Board::rowToPosY(int row) {
    return BOARD_SIZE - row;
}

bool Board::isOnBoard(Pos pos) {
    return pos.x >= 0 && pos.x < BOARD_SIZE && pos.y >= 0 && pos.y < BOARD_SIZE;
}

Board Board::afterDrop(Pos pos, PieceType type) const {
    Board board = *this;
    board.setPos(pos, type);
    return board;
}

PieceType Board::getPos(Pos pos) const {
    return board[pos.x][pos.y];
}

bool Board::setPos(Pos pos, PieceType type) {
    board[pos.x][pos.y] = type;
    return true;
}

bool Board::isEmpty(Pos pos) {
    return getPos(pos) == PieceType::EMPTY;
}

void Board::clearBoard() {
    for (int i = 0; i < Board::BOARD_SIZE; i++) {
        for (int j = 0; j < Board::BOARD_SIZE; j++) {
            setPos(Pos(i, j), PieceType::EMPTY);
        }
    }
}

PieceType Board::opponentOf(PieceType type) {
    return (type == PieceType::BLACK) ? PieceType::WHITE : PieceType::BLACK;
}

std::string Board::toString() const {
    std::stringstream ss;
    for (int i = BOARD_SIZE; i >= 1; i--) {
        ss << std::setw(2) << i << toStringRow(i) << "\n";
    }
    ss << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        ss << " " << char('A' + i) << " ";
    }
    return ss.str();
}

std::string Board::toString(const std::unordered_map<Pos, std::string, PosHash>* highlights) const {
    std::stringstream ss;
    for (int i = BOARD_SIZE; i >= 1; i--) {
        ss << std::setw(2) << i << toStringRow(i, highlights) << "\n";
    }
    ss << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        ss << " " << char('A' + i) << " ";
    }
    return ss.str();
}

std::string Board::pieceToString(const PieceType type) const {
    switch (type)
    {
    case PieceType::EMPTY:
        return " . ";
    case PieceType::BLACK:
        return " ● ";
    case PieceType::WHITE:
        return " ○ ";
    default:
        return " ? ";
    }
}

/*
std::string Board::toStringRow(int row) const {
    std::stringstream ss;
    for (int i = 0; i < BOARD_SIZE; i++) {
        switch (getPos(Pos(i, BOARD_SIZE - row)))
        {
        case PieceType::EMPTY:
            ss << " . ";
            break;
        case PieceType::BLACK:
            ss << " ● ";
            break;
        case PieceType::WHITE:
            ss << " ○ ";
            break;
        default:
            ss << " ? ";
            break;
        }
    }
    return ss.str();
}
    */

std::string Board::toStringRow(int row, const std::unordered_map<Pos, std::string, PosHash>* highlights) const {
    std::stringstream ss;
    for (int i = 0; i < BOARD_SIZE; i++) {
        Pos pos(i, BOARD_SIZE - row);
        if (highlights && highlights->count(pos)) {
            ss << (*highlights).at(pos);
        } else {
            ss << pieceToString(getPos(pos));
        }
    }
    return ss.str();
}