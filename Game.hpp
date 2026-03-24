#pragma once
#include <vector>
#include "Board.hpp"

class Game
{
public:
    Game();
    void printHistory() const;
    void printBoardAtMove(int);
    void makeMove(int, int, int, int);
    uint8_t getPieceAt(int, int);
    Board& getCurrentBoard();

private:
    Board currentBoard{};
    std::vector<Board> gameHistory;
    int currentTurn{};
};

