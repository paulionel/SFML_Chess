#pragma once
#include <cstdint>

// Piece and Color definitions
constexpr uint8_t EMPTY = 0;      // 0000 0000
constexpr uint8_t PAWN = 1;       // 0000 0001
constexpr uint8_t ROOK = 2;       // 0000 0010
constexpr uint8_t KNIGHT = 3;     // 0000 0011
constexpr uint8_t BISHOP = 4;     // 0000 0100
constexpr uint8_t QUEEN = 5;      // 0000 0101
constexpr uint8_t KING = 6;       // 0000 0110
constexpr uint8_t PIECE_MASK = 7; // 0000 0111
constexpr uint8_t BLACK = 8;      // 0000 1000
constexpr uint8_t WHITE = 0;      // 0000 0000