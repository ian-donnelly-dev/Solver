#include "board.hpp"

namespace {
    int popcount(const uint64_t bitboard) {
        return __builtin_popcountll(bitboard);
    }

    int getColumnHeight(const board::Position &position, const int column) {
        const uint64_t columnMask = board::FIRST_COLUMN_MASK << column * board::RIGHT_OFFSET;
        return popcount((position.p1Bitboard | position.p2Bitboard) & columnMask);
    }

    bool hasFourInARow(const uint64_t &bitboard, const int shift) {
        const uint64_t consecutive = bitboard & bitboard >> shift;
        return (consecutive & consecutive >> 2 * shift) != 0;
    }
}

namespace board {
    bool isPlayer1Turn(const Position &position) {
        return popcount(position.p1Bitboard) == popcount(position.p2Bitboard);
    }

    bool isColumnPlayable(const Position &position, const int column) {
        return getColumnHeight(position, column) < NUM_ROWS;
    }

    void makeMove(Position &position, const int column) {
        const uint64_t moveBit = 1ULL << column * RIGHT_OFFSET + getColumnHeight(position, column);

        if (isPlayer1Turn(position)) {
            position.p1Bitboard |= moveBit;
        } else {
            position.p2Bitboard |= moveBit;
        }
    }

    bool hasWinner(const Position &position) {
        const uint64_t lastPlayedBitboard = isPlayer1Turn(position) ? position.p2Bitboard : position.p1Bitboard;

        return hasFourInARow(lastPlayedBitboard, RIGHT_OFFSET + UP_OFFSET) ||
               hasFourInARow(lastPlayedBitboard, RIGHT_OFFSET - UP_OFFSET) ||
               hasFourInARow(lastPlayedBitboard, RIGHT_OFFSET) ||
               hasFourInARow(lastPlayedBitboard, UP_OFFSET);
    }

    bool isBoardFull(const Position &position) {
        return popcount(position.p1Bitboard | position.p2Bitboard) == NUM_ROWS * NUM_COLS;
    }
}
