#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

void drawBoard(sf::RenderWindow& window)
{

    // Draw the outside border of the chess board
    sf::RectangleShape boarder_square(sf::Vector2f(840.f, 840.f));
    boarder_square.setFillColor(sf::Color::Red);
    boarder_square.setPosition(sf::Vector2f(80.f, 80.f));

    window.draw(boarder_square);

    // Draw each square of the chessboard
    sf::RectangleShape white_square(sf::Vector2f(100.f, 100.f));
    white_square.setFillColor(sf::Color::White);

    sf::RectangleShape black_square(sf::Vector2f(100.f, 100.f));
    black_square.setFillColor(sf::Color::Black);

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

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "Chess Board");

    // King - White
    sf::Texture kingWTexture = loadTexture("images/king_white.png");
    sf::Sprite kingW(kingWTexture);
    kingW.setPosition({ 500.f, 800.f });

    // Queen - White
    sf::Texture queenWTexture = loadTexture("images/queen_white.png");
    sf::Sprite queenW(queenWTexture);
    queenW.setPosition({ 400.f, 800.f });


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        drawBoard(window);
        
        window.draw(kingW);
        window.draw(queenW);

        window.display();
    }
}