#include "Game.hpp"
#include <iostream>

Game::Game() : currentTurn(0)
{
    currentBoard.setup();
    gameHistory.push_back(currentBoard);
}

void Game::makeMove(int fromX, int fromY, int toX, int toY)
{
    uint8_t pieceToMove = currentBoard.get(fromX, fromY);

    Move move{ fromX, fromY, toX, toY, currentBoard.get(fromX, fromY) };
    moveHistory.push_back(move);

    currentBoard.set(fromX, fromY, 0);
    currentBoard.set(toX, toY, pieceToMove);

    currentTurn++;
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

int Game::getCurrentTurn()
{
    return currentTurn;
}
