#include "GameLogic.hpp"
#include <iostream>

bool canHighlight(int x, int y, Board& currentBoard, int currentTurn)
{
	if (currentBoard.get(x, y) & BLACK)
	{
		// The piece is black
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
	else
	{
		// The piece is white
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
}

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

std::vector<std::pair<int, int>> getPossibleBishopMoves(int x, int y, Board& currentBoard, int currentTurn)
{
	std::vector<std::pair<int, int>> possibleMoves{};

	// Checks down right
	for (int i = y + 1, j = x + 1; i <= 7 && j <= 7; i++, j++)
	{
		std::cout << "Current Turn: " << currentTurn << '\n';
		std::cout << "Piece at " << j << ", " << i << ": " << static_cast<int>(currentBoard.get(j, i)) << '\n';

		if (static_cast<int>(currentBoard.get(j, i)) != 0)
		{
			if (canAttack(j, i, currentBoard, currentTurn))
			{
				possibleMoves.push_back(std::pair<int, int> {j, i});
			}

			break;
		}
		else
		{
			possibleMoves.push_back(std::pair<int, int> {j, i});
		}
	}

	// Checks up right
	for (int i = y - 1, j = x + 1; i >= 0 && j <= 7; i--, j++)
	{
		std::cout << "Piece at " << j << ", " << i << ": " << static_cast<int>(currentBoard.get(j, i)) << '\n';

		if (static_cast<int>(currentBoard.get(j, i)) != 0)
		{
			if (canAttack(j, i, currentBoard, currentTurn))
			{
				possibleMoves.push_back(std::pair<int, int> {j, i});
			}

			break;
		}
		else
		{
			possibleMoves.push_back(std::pair<int, int> {j, i});
		}
	}

	// Checks up left
	for (int i = y - 1, j = x - 1; i >= 0 && j >= 0; i--, j--)
	{
		std::cout << "Piece at " << j << ", " << i << ": " << static_cast<int>(currentBoard.get(j, i)) << '\n';

		if (static_cast<int>(currentBoard.get(j, i)) != 0)
		{
			if (canAttack(j, i, currentBoard, currentTurn))
			{
				possibleMoves.push_back(std::pair<int, int> {j, i});
			}

			break;
		}
		else
		{
			possibleMoves.push_back(std::pair<int, int> {j, i});
		}
	}

	// Checks down left
	for (int i = y + 1, j = x - 1; i <= 7 && j >= 0; i++, j--)
	{
		std::cout << "Current Turn: " << currentTurn << '\n';
		std::cout << "Piece at " << j << ", " << i << ": " << static_cast<int>(currentBoard.get(j, i)) << '\n';

		if (static_cast<int>(currentBoard.get(j, i)) != 0)
		{
			if (canAttack(j, i, currentBoard, currentTurn))
			{
				possibleMoves.push_back(std::pair<int, int> {j, i});
			}

			break;
		}
		else
		{
			possibleMoves.push_back(std::pair<int, int> {j, i});
		}
	}

	return possibleMoves;
}

std::vector<std::pair<int, int>> possibleMoveManager(int x, int y, Board& currentBoard, int currentTurn)
{
	if (currentBoard.get(x, y) & ROOK)
	{
		return getPossibleRookMoves(x, y, currentBoard, currentTurn);
	}
	if (currentBoard.get(x, y) & KNIGHT)
	{
		// not right, but put it here for now so I don't get errors
		return getPossibleRookMoves(x, y, currentBoard, currentTurn);
	}
	if (currentBoard.get(x, y) & BISHOP)
	{
		return getPossibleBishopMoves(x, y, currentBoard, currentTurn);
	}
	if (currentBoard.get(x, y) & QUEEN)
	{
		// not right, but put it here for now so I don't get errors
		return getPossibleRookMoves(x, y, currentBoard, currentTurn);
	}
	if (currentBoard.get(x, y) & KING)
	{
		// not right, but put it here for now so I don't get errors
		return getPossibleRookMoves(x, y, currentBoard, currentTurn);
	}
	if (currentBoard.get(x, y) & PAWN)
	{
		// not right, but put it here for now so I don't get errors
		return getPossibleRookMoves(x, y, currentBoard, currentTurn);
	}
}