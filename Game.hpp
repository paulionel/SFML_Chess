#pragma once
#include <vector>
#include "Board.hpp"

struct Move
{
    int fromX, fromY;
    int toX, toY;
    uint8_t piece;
};

class Game
{
public:
    Game();
    void printHistory() const;
    void printBoardAtMove(int);
    void makeMove(int, int, int, int);
    uint8_t getPieceAt(int, int);
    Board& getCurrentBoard();
    int getCurrentTurn();

private:
    Board currentBoard{};
    std::vector<Board> gameHistory;
    std::vector<Move> moveHistory;
    int currentTurn{};
};

