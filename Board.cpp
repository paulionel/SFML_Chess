#include "Board.hpp"
#include "GameLogic.hpp"
#include <iostream>

Board::Board() {}

void Board::setup()
{
    squares[0][0] = BLACK | ROOK;
    squares[0][1] = BLACK | KNIGHT;
    squares[0][2] = BLACK | BISHOP;
    squares[0][3] = BLACK | QUEEN;
    squares[0][4] = BLACK | KING;
    squares[0][5] = BLACK | BISHOP;
    squares[0][6] = BLACK | KNIGHT;
    squares[0][7] = BLACK | ROOK;

    squares[1][0] = BLACK | PAWN;
    squares[1][1] = BLACK | PAWN;
    squares[1][2] = BLACK | PAWN;
    squares[1][3] = BLACK | PAWN;
    squares[1][4] = BLACK | PAWN;
    squares[1][5] = BLACK | PAWN;
    squares[1][6] = BLACK | PAWN;
    squares[1][7] = BLACK | PAWN;

    squares[7][0] = WHITE | ROOK;
    squares[7][1] = WHITE | KNIGHT;
    squares[7][2] = WHITE | BISHOP;
    squares[7][3] = WHITE | QUEEN;
    squares[7][4] = WHITE | KING;
    squares[7][5] = WHITE | BISHOP;
    squares[7][6] = WHITE | KNIGHT;
    squares[7][7] = WHITE | ROOK;

    squares[6][0] = WHITE | PAWN;
    squares[6][1] = WHITE | PAWN;
    squares[6][2] = WHITE | PAWN;
    squares[6][3] = WHITE | PAWN;
    squares[6][4] = WHITE | PAWN;
    squares[6][5] = WHITE | PAWN;
    squares[6][6] = WHITE | PAWN;
    squares[6][7] = WHITE | PAWN;
}

uint8_t Board::get(int x, int y) const
{
    return squares[y][x];
}

void Board::set(int x, int y, uint8_t value)
{
    squares[y][x] = value;
}

void Board::printBoard() const
{
    for (int row = 0; row < SIZE; ++row)
    {
        for (int col = 0; col < SIZE; ++col)
        {
            std::cout << static_cast<int>(get(col, row)) << " ";
        }
        std::cout << "\n";
    }
}