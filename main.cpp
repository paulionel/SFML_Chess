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


constexpr float TILE_SIZE = 100.f;


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

void drawCircle(sf::RenderWindow& window, float x, float y)
{
    sf::CircleShape circle(10);
    circle.setFillColor(sf::Color(97, 100, 103));
    circle.setPosition(sf::Vector2f((x * 100) + 40, (y * 100) + 40));

    window.draw(circle);
}

void drawHighlight(sf::RenderWindow& window, float& x, float& y)
{
    sf::RectangleShape highlight(sf::Vector2f(100.f, 100.f));
    highlight.setFillColor(sf::Color(113, 198, 217));
    highlight.setPosition(sf::Vector2f(x * 100, y * 100));

    window.draw(highlight);
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

bool loadTexture(sf::Texture& texture, const std::string& path)
{
    if (!texture.loadFromFile(path))
    {
        std::cout << "Failed to load texture: " << path << '\n';
        return false;
    }
    return true;
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

int main()
{

    setupBoard();

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

    //getBoard();

    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "Chess Board");

    bool highlighted{};

    float selectedX{};
    float selectedY{};

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

                    selectedX = static_cast<float>(mouseX / 100);
                    selectedY = static_cast<float>(mouseY / 100);

                    std::cout << "Selected X Position: " << selectedX << '\n';
                    std::cout << "Selected Y Position: " << selectedY << '\n';

                    if (static_cast<int>(board[(mouseY / 100) - 1][(mouseX / 100) - 1]) != 0)
                    {
                        std::cout << "Hit Piece: " << static_cast<int>(board[(mouseY / 100) - 1][(mouseX / 100) - 1]) << '\n';
                        highlighted = true;
                    } 
                    else
                    {
                        highlighted = false;
                    } 
                }
            }
        }

        window.clear();

        drawBoard(window);

        if (highlighted)
            drawHighlight(window, selectedX, selectedY);

        drawCircle(window, 5, 5);
        drawCircle(window, 5, 6);

        drawPieces(window, textures);

        window.display();
    }
}