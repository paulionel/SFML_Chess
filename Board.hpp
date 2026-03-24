#pragma once
#include <cstdint>

class Board
{
public:
    static constexpr int SIZE = 8;

    Board();
    void setup();
    void printBoard() const;

    uint8_t get(int x, int y) const;
    void set(int x, int y, uint8_t value);

private:
    uint8_t squares[SIZE][SIZE]{};
};