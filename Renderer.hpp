#pragma once
#include <SFML/Graphics.hpp>
#include "GameLogic.hpp"
#include "Board.hpp"

constexpr float TILE_SIZE = 100.f;

bool loadTexture(sf::Texture& texture, const std::string& path);

void drawBoard(sf::RenderWindow& window);
void drawPieces(sf::RenderWindow& window, const sf::Texture textures[], Board& currentBoard);
void drawHighlight(sf::RenderWindow& window, int x, int y);
void drawCircle(sf::RenderWindow& window, float x, float y);