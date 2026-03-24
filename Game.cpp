#include "Game.hpp"
#include <iostream>

Game::Game() : currentTurn(0)
{
    currentBoard.setup();
    gameHistory.push_back(currentBoard);
}

void Game::makeMove(int fromX, int fromY, int toX, int toY)
{
    int pieceToMove = currentBoard.get(fromX, fromY); // Pretty sure this should be a uint8_t rather than a int, but i'll look into it later
    currentBoard.set(fromX, fromY, 0);
    currentBoard.set(toX, toY, pieceToMove);
    currentTurn += 1;
    gameHistory.push_back(currentBoard);
}

void Game::printHistory() const
{
    for (size_t i = 0; i < gameHistory.size(); i++)
    {
        std::cout << "Board " << i << ":\n";
        gameHistory[i].printBoard();
        std::cout << "\n";
    }
}

void Game::printBoardAtMove(int turn)
{
    std::cout << "Board at turn " << turn << ":\n";
    gameHistory[turn].printBoard();
    std::cout << "\n";
}

uint8_t Game::getPieceAt(int x, int y)
{
    return currentBoard.get(x, y);
}

Board& Game::getCurrentBoard()
{
    return currentBoard;
}
