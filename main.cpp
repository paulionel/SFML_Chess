#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

// Piece and Color definitions
constexpr uint8_t EMPTY = 0;      // 0000 0000
constexpr uint8_t PAWN = 1;       // 0000 0001
constexpr uint8_t ROOK = 2;       // 0000 0010
constexpr uint8_t KNIGHT = 3;     // 0000 0011
constexpr uint8_t BISHOP = 4;     // 0000 0100
constexpr uint8_t QUEEN = 5;      // 0000 0101
constexpr uint8_t KING = 6;       // 0000 0110
constexpr uint8_t PIECE_MASK = 7; // 0000 0111
constexpr uint8_t BLACK = 8;      // 0000 1000
constexpr uint8_t WHITE = 0;      // 0000 0000


uint8_t board[8][8]; // Just for now, eventually we will make this not global

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

void getBoard()
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

void drawBoard(sf::RenderWindow& window)
{

    // Draw the outside border of the chess board
    sf::RectangleShape boarder_square(sf::Vector2f(840.f, 840.f));
    boarder_square.setFillColor(sf::Color(97, 100, 103));
    boarder_square.setPosition(sf::Vector2f(80.f, 80.f));

    window.draw(boarder_square);

    // Draw each square of the chessboard
    sf::RectangleShape white_square(sf::Vector2f(100.f, 100.f));
    white_square.setFillColor(sf::Color(228, 240, 242));

    sf::RectangleShape black_square(sf::Vector2f(100.f, 100.f));
    black_square.setFillColor(sf::Color(111, 150, 166));

    float x_position{ 0 };
    float y_position{ 0 };

    for (int row{ 1 }; row <= 8; ++row)
    {
        y_position = row * 100;

        for (int column{ 1 }; column <= 8; ++column)
        {
            x_position = column * 100;

            if ((row + column) % 2 == 0)
            {
                white_square.setPosition(sf::Vector2f(x_position, y_position));
                window.draw(white_square);
            }
            else
            {
                black_square.setPosition(sf::Vector2f(x_position, y_position));
                window.draw(black_square);
            }
        }
    }
}

sf::Texture loadTexture(const std::string& path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(path))
    {
        std::cout << "Failed to load texture: " << path << "\n";
    }
    return texture;
}

std::string getPiecePath(const uint8_t& piece)
{
    if (piece == 1)
        return "images/pawn_white.png";
    else if (piece == 2)
        return "images/rook_white.png";
    else if (piece == 3)
        return "images/knight_white.png";
    else if (piece == 4)
        return "images/bishop_white.png";
    else if (piece == 5)
        return "images/queen_white.png";
    else if (piece == 6)
        return "images/king_white.png";
    else if (piece == 9)
        return "images/pawn_black.png";
    else if (piece == 10)
        return "images/rook_black.png";
    else if (piece == 11)
        return "images/knight_black.png";
    else if (piece == 12)
        return "images/bishop_black.png";
    else if (piece == 13)
        return "images/queen_black.png";
    else if (piece == 14)
        return "images/king_black.png";
}

void drawPieces(sf::RenderWindow& window)
{
    float x_position{ 0 };
    float y_position{ 0 };
    for (int row = 0; row < 8; ++row)
    {
        y_position = (row + 1) * 100;
        for (int col = 0; col < 8; ++col)
        {
            x_position = (col + 1) * 100;
            uint8_t piece = board[row][col];

            if (piece != EMPTY)
            {
                sf::Texture texture = loadTexture(getPiecePath(piece));
                sf::Sprite sprite(texture);
                sprite.setPosition({ x_position, y_position });

                window.draw(sprite);
            }
        }
    }
}

int main()
{

    setupBoard();

    //getBoard();

    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "Chess Board");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        drawBoard(window);

        drawPieces(window);

        window.display();
    }
}