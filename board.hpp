#pragma once

#include <cstdint>

namespace board {
    constexpr int NUM_ROWS = 6;
    constexpr int NUM_COLS = 7;
    constexpr int UP_OFFSET = 1;
    constexpr int RIGHT_OFFSET = NUM_ROWS + 1;
    constexpr uint64_t FIRST_COLUMN_MASK = (1ULL << NUM_ROWS) - 1;

    struct Position {
        uint64_t p1Bitboard = 0ULL;
        uint64_t p2Bitboard = 0ULL;
    };

    bool isPlayer1Turn(const Position& position);
    bool isColumnPlayable(const Position& position, int column);
    void applyMove(Position& position, int column);
    bool hasWinner(const Position& position);
    bool isBoardFull(const Position& position);
}
