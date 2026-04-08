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

bool isInbounds(int x, int y)
{
	if (x >= 0 && x <= 7 && y >= 0 && y <= 7) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool containsPossibleMove(const std::vector<std::pair<int, int>>& moves, int x, int y)
{
	for (const auto& move : moves)
	{
		if (move.first == x && move.second == y)
		{
			return true;
		}
	}
	return false;
}

std::vector<std::pair<int, int>> getPossiblePawnMoves(int x, int y, Board& currentBoard, int currentTurn, const std::vector<Move>& moveHistory)
{
	std::vector<std::pair<int, int>> possibleMoves{};

	uint8_t piece = currentBoard.get(x, y);
	bool isBlack = piece & BLACK;

	int direction = isBlack ? 1 : -1;
	int startRow = isBlack ? 1 : 6;

	// Forward 1
	int forwardY = y + direction;

	if (isInbounds(x, forwardY) && currentBoard.get(x, forwardY) == EMPTY)
	{
		possibleMoves.push_back({ x, forwardY });

		// Forward 2 (only if first move AND path is clear)
		int doubleY = y + (2 * direction);
		if (y == startRow && currentBoard.get(x, doubleY) == EMPTY)
		{
			possibleMoves.push_back({ x, doubleY });
		}
	}

	// Captures (diagonals)
	for (int dx : {-1, 1})
	{
		int newX = x + dx;
		int newY = y + direction;

		if (!isInbounds(newX, newY))
			continue;

		uint8_t target = currentBoard.get(newX, newY);

		if (target != EMPTY && canAttack(newX, newY, currentBoard, currentTurn))
		{
			possibleMoves.push_back({ newX, newY });
		}
	}

	// En Passant
	if (!moveHistory.empty())
	{
		const Move& lastMove = moveHistory.back();

		// Check if last move was a pawn
		if ((lastMove.piece & PIECE_MASK) == PAWN)
		{
			int moveDistance = std::abs(lastMove.toY - lastMove.fromY);

			// Must be a 2-square move
			if (moveDistance == 2)
			{
				// Pawn must be next to us
				if (lastMove.toY == y && std::abs(lastMove.toX - x) == 1)
				{
					int enPassantX = lastMove.toX;
					int enPassantY = y + direction;

					possibleMoves.push_back({ enPassantX, enPassantY });
				}
			}
		}
	}

	return possibleMoves;
}

std::vector<std::pair<int, int>> getPossibleRookMoves(int x, int y, Board& currentBoard, int currentTurn)
{
	std::vector<std::pair<int, int>> possibleMoves{};

	// Checks down
	for (int i = y + 1; i <= 7; i++)
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

std::vector<std::pair<int, int>> getPossibleKnightMoves(int x, int y, Board& currentBoard, int currentTurn)
{
	std::vector<std::pair<int, int>> possibleMoves{};

	std::vector<std::pair<int, int>> knightMoves = {
		{-1, -2}, {1, -2},
		{2, -1},  {2, 1},
		{-1, 2},  {1, 2},
		{-2, -1}, {-2, 1}
	};

	for (auto& move : knightMoves)
	{
		int newX = x + move.first;
		int newY = y + move.second;

		// Check bounds
		if (!isInbounds(newX, newY))
			continue;

		uint8_t piece = currentBoard.get(newX, newY);

		// Empty square
		if (piece == EMPTY)
		{
			possibleMoves.push_back(std::pair<int, int> {newX, newY});
		}
		// Occupied > check if attackable
		else if (canAttack(newX, newY, currentBoard, currentTurn))
		{
			possibleMoves.push_back(std::pair<int, int> {newX, newY});
		}
	}

	return possibleMoves;
}

std::vector<std::pair<int, int>> getPossibleQueenMoves(int x, int y, Board& currentBoard, int currentTurn)
{
	std::vector<std::pair<int, int>> possibleMoves{};

	// Checks down
	for (int i = y + 1; i <= 7; i++)
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

	// Checks down right
	for (int i = y + 1, j = x + 1; i <= 7 && j <= 7; i++, j++)
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

std::vector<std::pair<int, int>> possibleMoveManager(int x, int y, Board& currentBoard, int currentTurn, const std::vector<Move>& moveHistory)
{
	uint8_t piece = currentBoard.get(x, y) & PIECE_MASK;

	if (piece == ROOK)
	{
		std::cout << "I'm a rook!" << "\n";
		return getPossibleRookMoves(x, y, currentBoard, currentTurn);
	}
	if (piece == KNIGHT)
	{
		std::cout << "I'm a knight!" << "\n";
		return getPossibleKnightMoves(x, y, currentBoard, currentTurn);
	}
	if (piece == BISHOP)
	{
		std::cout << "I'm a bishop!" << "\n";
		return getPossibleBishopMoves(x, y, currentBoard, currentTurn);
	}
	if (piece == QUEEN)
	{
		std::cout << "I'm a queen!" << "\n";
		return getPossibleQueenMoves(x, y, currentBoard, currentTurn);
	}
	if (piece == KING)
	{
		std::cout << "I'm a king!" << "\n";
		// not right, but put it here for now so I don't get errors
		return getPossibleRookMoves(x, y, currentBoard, currentTurn);
	}
	if (piece == PAWN)
	{
		std::cout << "I'm a pawn!" << "\n";
		return getPossiblePawnMoves(x, y, currentBoard, currentTurn, moveHistory);
	}
	return {};
}