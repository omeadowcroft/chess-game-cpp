#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "board.h"

extern std::map<std::string, sf::Texture> textures;

void loadTextures();
void renderBoard(sf::RenderWindow& window, chessPiece board[8][8], float squareSize, int boardStartX, int boardStartY);


