#include "GameLogic.hpp"
#include <iostream>

bool canAttack(int x, int y, Board& currentBoard, int currentTurn)
{
	if (currentBoard.get(x, y) & BLACK)
	{
		// The piece is black
		if (currentTurn % 2 == 0)
		{
			// It's white's turn
			return true;
		}
		else
		{
			// It's black's turn
			return false;
		}
	}
	else
	{
		// The piece is white
		if (currentTurn % 2 == 0)
		{
			// It's white's turn
			return false;
		}
		else
		{
			// It's black's turn
			return true;
		}
	}
}

std::vector<std::pair<int, int>> getPossibleRookMoves(int x, int y, Board& currentBoard, int currentTurn)
{
	std::vector<std::pair<int, int>> possibleMoves{};

	// Checks down
	for (int i = y + 1; i <= 7; i++)
	{
		std::cout << "Current Turn: " << currentTurn << '\n';
		std::cout << "Piece at " << x << ", " << i << ": " << static_cast<int>(currentBoard.get(x, i)) << '\n';

		if (static_cast<int>(currentBoard.get(x, i)) != 0)
		{
			if (canAttack(x, i, currentBoard, currentTurn))
			{
				possibleMoves.push_back(std::pair<int, int> {x, i});
			}

			break;
		}
		else
		{
			possibleMoves.push_back(std::pair<int, int> {x, i});
		}
	}

	// Checks up
	for (int i = y - 1; i >= 0; i--)
	{
		std::cout << "Piece at " << x << ", " << i << ": " << static_cast<int>(currentBoard.get(x, i)) << '\n';

		if (static_cast<int>(currentBoard.get(x, i)) != 0)
		{
			if (canAttack(x, i, currentBoard, currentTurn))
			{
				possibleMoves.push_back(std::pair<int, int> {x, i});
			}

			break;
		}
		else
		{
			possibleMoves.push_back(std::pair<int, int> {x, i});
		}
	}

	// Checks right
	for (int i = x + 1; i <= 7; i++)
	{
		std::cout << "Piece at " << i << ", " << y << ": " << static_cast<int>(currentBoard.get(i, y)) << '\n';

		if (static_cast<int>(currentBoard.get(i, y)) != 0)
		{
			if (canAttack(i, y, currentBoard, currentTurn))
			{
				possibleMoves.push_back(std::pair<int, int> {i, y});
			}

			break;
		}
		else
		{
			possibleMoves.push_back(std::pair<int, int> {i, y});
		}
	}

	// Checks left
	for (int i = x - 1; i >= 0; i--)
	{
		std::cout << "Piece at " << i << ", " << y << ": " << static_cast<int>(currentBoard.get(i, y)) << '\n';

		if (static_cast<int>(currentBoard.get(i, y)) != 0)
		{
			if (canAttack(i, y, currentBoard, currentTurn))
			{
				possibleMoves.push_back(std::pair<int, int> {i, y});
			}

			break;
		}
		else
		{
			possibleMoves.push_back(std::pair<int, int> {i, y});
		}
	}

	return possibleMoves;
}