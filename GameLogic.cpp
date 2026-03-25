#include "GameLogic.hpp"
#include <iostream>

std::vector<std::pair<int, int>> getPossibleRookMoves(int x, int y, Board& currentBoard, int currentTurn)
{
	std::vector<std::pair<int, int>> possibleMoves{};

	std::pair<int, int> p1 = { 1, 1 };

	possibleMoves.push_back(p1);

	for (int i = y + 1; i <= 7; i++)
	{
		std::cout << "Piece at " << x << ", " << i << ": " << static_cast<int>(currentBoard.get(x, i)) << '\n';
		std::cout << "Current Turn: " << currentTurn << '\n';

		if (static_cast<int>(currentBoard.get(x, i)) != 0)
		{
			if (currentBoard.get(x, i) & BLACK)
			{
				std::cout << "Piece is black" << '\n';
				if (currentTurn % 2 == 0)
				{
					std::cout << "It's whites's turn. You can't attack that piece" << '\n';
				}
				else
				{
					std::cout << "It's black's turn. You can attack that piece" << '\n';
				}
			}
			else
			{
				std::cout << "Piece is white" << '\n';
				if (currentTurn % 2 == 0)
				{
					std::cout << "It's whites's turn. You can't attack that piece" << '\n';
				}
				else
				{
					std::cout << "It's black's turn. You can attack that piece" << '\n';
				}
			}
		}
	}
	for (int i = y - 1; i >= 0; i--)
	{
		std::cout << "Piece at " << x << ", " << i << ": " << static_cast<int>(currentBoard.get(x, i)) << '\n';
	}
	for (int i = x + 1; i <= 7; i++)
	{
		std::cout << "Piece at " << i << ", " << y << ": " << static_cast<int>(currentBoard.get(i, y)) << '\n';
	}
	for (int i = x - 1; i >= 0; i--)
	{
		std::cout << "Piece at " << i << ", " << y << ": " << static_cast<int>(currentBoard.get(i, y)) << '\n';
	}

	return possibleMoves;
}