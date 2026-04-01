#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "GameLogic.hpp"
#include "Renderer.hpp"
#include <iostream>
#include <fstream>


int main()
{

    Game game;

    std::vector<std::pair<int, int>> possibleMoves{};

    sf::Texture textures[16];

    loadTexture(textures[WHITE | PAWN], "images/pawn_white.png");
    loadTexture(textures[WHITE | ROOK], "images/rook_white.png");
    loadTexture(textures[WHITE | KNIGHT], "images/knight_white.png");
    loadTexture(textures[WHITE | BISHOP], "images/bishop_white.png");
    loadTexture(textures[WHITE | QUEEN], "images/queen_white.png");
    loadTexture(textures[WHITE | KING], "images/king_white.png");

    loadTexture(textures[BLACK | PAWN], "images/pawn_black.png");
    loadTexture(textures[BLACK | ROOK], "images/rook_black.png");
    loadTexture(textures[BLACK | KNIGHT], "images/knight_black.png");
    loadTexture(textures[BLACK | BISHOP], "images/bishop_black.png");
    loadTexture(textures[BLACK | QUEEN], "images/queen_black.png");
    loadTexture(textures[BLACK | KING], "images/king_black.png");

    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "Chess Board");

    bool highlighted{};

    int selectedX{};
    int selectedY{};

    int highlightedX{};
    int highlightedY{};

    while (window.isOpen())
    {
        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::MouseButtonPressed>())
            {
                auto mouse = event->getIf<sf::Event::MouseButtonPressed>();

                if (mouse->button == sf::Mouse::Button::Left)
                {
                    int mouseX = mouse->position.x;
                    int mouseY = mouse->position.y;

                    std::cout << "Mouse X Position: " << mouseX << '\n';
                    std::cout << "Mouse Y Position: " << mouseY << '\n';

                    selectedX = mouseX / 100;
                    selectedY = mouseY / 100;

                    std::cout << "Selected X Position: " << selectedX << '\n';
                    std::cout << "Selected Y Position: " << selectedY << '\n';

                    if (containsPossibleMove(possibleMoves, selectedX - 1, selectedY - 1))
                    {
                        std::cout << "Move exists!\n";

                        game.makeMove(highlightedX - 1, highlightedY - 1, selectedX - 1, selectedY - 1);

                        highlighted = false;
                        possibleMoves.clear();
                    }
                    else if (static_cast<int>(game.getPieceAt((mouseX / 100) - 1,(mouseY / 100) - 1)) != 0 && canHighlight((mouseX / 100) - 1, (mouseY / 100) - 1, game.getCurrentBoard(), game.getCurrentTurn()))
                    {

                        std::cout << "Hit Piece: " << static_cast<int>(game.getPieceAt((mouseX / 100) - 1, (mouseY / 100) - 1)) << '\n';

                        highlightedX = mouseX / 100;
                        highlightedY = mouseY / 100;
                        highlighted = true;
                        possibleMoves = possibleMoveManager((mouseX / 100) - 1, (mouseY / 100) - 1, game.getCurrentBoard(), game.getCurrentTurn());
                    } 
                    else
                    {
                        highlighted = false;
                        possibleMoves.clear();
                    } 
                }
            }
        }

        window.clear();

        drawBoard(window);

        if (highlighted)
            drawHighlight(window, highlightedX, highlightedY);

        drawPieces(window, textures, game.getCurrentBoard());

        for (const auto& [x, y] : possibleMoves)
        {
            drawCircle(window, x, y);
        }

        window.display();
    }
}