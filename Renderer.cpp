#include "Renderer.hpp"
#include <iostream>

bool loadTexture(sf::Texture& texture, const std::string& path)
{
    if (!texture.loadFromFile(path))
    {
        std::cout << "Failed to load texture: " << path << '\n';
        return false;
    }
    return true;
}

void drawBoard(sf::RenderWindow& window)
{

    // Draw the outside border of the chess board
    sf::RectangleShape border_square(sf::Vector2f(840.f, 840.f));
    border_square.setFillColor(sf::Color(97, 100, 103));
    border_square.setPosition(sf::Vector2f(80.f, 80.f));

    window.draw(border_square);

    // Draw each square of the chessboard
    sf::RectangleShape white_square(sf::Vector2f(100.f, 100.f));
    white_square.setFillColor(sf::Color(228, 240, 242));

    sf::RectangleShape black_square(sf::Vector2f(100.f, 100.f));
    black_square.setFillColor(sf::Color(111, 150, 166));

    float x_position{ 0 };
    float y_position{ 0 };

    for (int row{ 1 }; row <= 8; ++row)
    {
        y_position = row * TILE_SIZE;

        for (int column{ 1 }; column <= 8; ++column)
        {
            x_position = column * TILE_SIZE;

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

void drawHighlight(sf::RenderWindow& window, int x, int y)
{
    sf::RectangleShape highlight(sf::Vector2f(100.f, 100.f));
    highlight.setFillColor(sf::Color(113, 198, 217));

    highlight.setPosition(sf::Vector2f(
        static_cast<float>(x) * TILE_SIZE,
        static_cast<float>(y) * TILE_SIZE
    ));

    window.draw(highlight);
}

void drawCircle(sf::RenderWindow& window, float x, float y)
{
    sf::CircleShape circle(10);
    circle.setFillColor(sf::Color(97, 100, 103));
    circle.setPosition(sf::Vector2f((x * 100) + 40, (y * 100) + 40));

    window.draw(circle);
}

void drawPieces(sf::RenderWindow& window, const sf::Texture textures[])
{
    float x_position{ 0 };
    float y_position{ 0 };
    for (int row = 0; row < 8; ++row)
    {
        y_position = (row + 1) * TILE_SIZE;
        for (int col = 0; col < 8; ++col)
        {
            x_position = (col + 1) * TILE_SIZE;
            uint8_t piece = board[row][col];

            if (piece != EMPTY)
            {
                sf::Sprite sprite(textures[piece]);
                sprite.setPosition({ x_position, y_position });

                window.draw(sprite);
            }
        }
    }
}