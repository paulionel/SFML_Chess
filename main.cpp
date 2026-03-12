#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "Chess Board");

    sf::RectangleShape boarder_square(sf::Vector2f(840.f, 840.f));
    boarder_square.setFillColor(sf::Color::Red);
    boarder_square.setPosition(sf::Vector2f(80.f, 80.f));

    sf::RectangleShape white_square(sf::Vector2f(100.f, 100.f));
    white_square.setFillColor(sf::Color::White);

    sf::RectangleShape black_square(sf::Vector2f(100.f, 100.f));
    black_square.setFillColor(sf::Color::Black);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(boarder_square);

        float x_position{ 0 };
        float y_position{ 0 };
        for (int row{ 1 }; row <= 8; ++row) 
        {
            y_position = row * 100;
            if (row % 2 != 0)
            {
                for (int column{ 1 }; column <= 8; ++column)
                {
                    x_position = column * 100;
                    if (column % 2 != 0)
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
            else
            {
                for (int column{ 1 }; column <= 8; ++column)
                {
                    x_position = column * 100;
                    if (column % 2 != 0)
                    {
                        black_square.setPosition(sf::Vector2f(x_position, y_position));
                        window.draw(black_square);
                    }
                    else
                    {
                        white_square.setPosition(sf::Vector2f(x_position, y_position));
                        window.draw(white_square);
                    }
                }
            }
        }


        window.display();
    }
}