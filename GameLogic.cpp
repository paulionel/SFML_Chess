#include "GameLogic.hpp"
#include <iostream>

uint8_t board[8][8]{}; // Just for now, eventually we will make this not global

void setupBoard()
{
    board[0][0] = BLACK | ROOK;
    board[0][1] = BLACK | KNIGHT;
    board[0][2] = BLACK | BISHOP;
    board[0][3] = BLACK | QUEEN;
    board[0][4] = BLACK | KING;
    board[0][5] = BLACK | BISHOP;
    board[0][6] = BLACK | KNIGHT;
    board[0][7] = BLACK | ROOK;

    board[1][0] = BLACK | PAWN;
    board[1][1] = BLACK | PAWN;
    board[1][2] = BLACK | PAWN;
    board[1][3] = BLACK | PAWN;
    board[1][4] = BLACK | PAWN;
    board[1][5] = BLACK | PAWN;
    board[1][6] = BLACK | PAWN;
    board[1][7] = BLACK | PAWN;

    board[7][0] = WHITE | ROOK;
    board[7][1] = WHITE | KNIGHT;
    board[7][2] = WHITE | BISHOP;
    board[7][3] = WHITE | QUEEN;
    board[7][4] = WHITE | KING;
    board[7][5] = WHITE | BISHOP;
    board[7][6] = WHITE | KNIGHT;
    board[7][7] = WHITE | ROOK;

    board[6][0] = WHITE | PAWN;
    board[6][1] = WHITE | PAWN;
    board[6][2] = WHITE | PAWN;
    board[6][3] = WHITE | PAWN;
    board[6][4] = WHITE | PAWN;
    board[6][5] = WHITE | PAWN;
    board[6][6] = WHITE | PAWN;
    board[6][7] = WHITE | PAWN;
}

void printBoard()
{
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            std::cout << static_cast<int>(board[row][col]) << " ";
        }
        std::cout << "\n";
    }
}