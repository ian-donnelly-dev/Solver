#include "board.hpp"

namespace {
    int popcount(const uint64_t bitboard) {
        return __builtin_popcountll(bitboard);
    }

    int getColumnHeight(const board::State &state, const int column) {
        const uint64_t columnMask = board::FIRST_COLUMN_MASK << column * board::RIGHT_OFFSET;
        return popcount((state.p1Bitboard | state.p2Bitboard) & columnMask);
    }

    bool hasFourInARow(const uint64_t &bitboard, const int shift) {
        const uint64_t consecutive = bitboard & bitboard >> shift;
        return (consecutive & consecutive >> 2 * shift) != 0;
    }
}

namespace board {
    bool isPlayer1Turn(const State &state) {
        return popcount(state.p1Bitboard) == popcount(state.p2Bitboard);
    }

    bool isColumnPlayable(const State &state, const int column) {
        return getColumnHeight(state, column) < NUM_ROWS;
    }

    void makeMove(State &state, const int column) {
        const uint64_t moveBit = 1ULL << column * RIGHT_OFFSET + getColumnHeight(state, column);

        if (isPlayer1Turn(state)) {
            state.p1Bitboard |= moveBit;
        } else {
            state.p2Bitboard |= moveBit;
        }
    }

    bool hasWinner(const State &state) {
        const uint64_t lastPlayedBitboard = isPlayer1Turn(state) ? state.p2Bitboard : state.p1Bitboard;

        return hasFourInARow(lastPlayedBitboard, RIGHT_OFFSET + UP_OFFSET) ||
               hasFourInARow(lastPlayedBitboard, RIGHT_OFFSET - UP_OFFSET) ||
               hasFourInARow(lastPlayedBitboard, RIGHT_OFFSET) ||
               hasFourInARow(lastPlayedBitboard, UP_OFFSET);
    }

    bool isBoardFull(const State &state) {
        return popcount(state.p1Bitboard | state.p2Bitboard) == NUM_ROWS * NUM_COLS;
    }
}
