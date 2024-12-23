#pragma once

#include <cstdint>

namespace board {
    constexpr int NUM_ROWS = 6;
    constexpr int NUM_COLS = 7;
    constexpr int UP_OFFSET = 1;
    constexpr int RIGHT_OFFSET = NUM_ROWS + 1;
    constexpr uint64_t FIRST_COLUMN_MASK = (1ULL << NUM_ROWS) - 1;

    struct State {
        uint64_t p1Bitboard = 0ULL;
        uint64_t p2Bitboard = 0ULL;
    };

    bool isPlayer1Turn(const State& state);
    bool isColumnPlayable(const State& state, int column);
    void makeMove(State& state, int column);
    bool hasWinner(const State& state);
    bool isBoardFull(const State& state);
}
