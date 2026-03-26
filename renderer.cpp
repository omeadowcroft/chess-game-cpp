#include "renderer.h"
#include "board.h"
#include <stdexcept>

std::map<std::string, sf::Texture> textures;

static void loadTexture(const std::string& name) {
    if (!textures[name].loadFromFile("assets/" + name + ".png"))
        throw std::runtime_error("Failed to load assets/" + name + ".png");
}

void loadTextures() {
    loadTexture("blackKing");
    loadTexture("blackQueen");
    loadTexture("blackRook");
    loadTexture("blackBishop");
    loadTexture("blackKnight");
    loadTexture("blackPawn");
    loadTexture("whiteKing");
    loadTexture("whiteQueen");
    loadTexture("whiteRook");
    loadTexture("whiteBishop");
    loadTexture("whiteKnight");
    loadTexture("whitePawn");

}

void renderBoard(sf::RenderWindow& window, chessPiece board[8][8], float squareSize, int boardStartX, int boardStartY) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            chessPiece&piece = board[row][col];
            if (piece.type == pieceType::none) continue;

            std::string colourStr = (piece.pieceColour == colour::white) ? "white" : "black";
            std::string typeStr;
            switch (piece.type) {
                case pieceType::pawn:   typeStr = "Pawn";   break;
                case pieceType::knight: typeStr = "Knight"; break;
                case pieceType::bishop: typeStr = "Bishop"; break;
                case pieceType::rook:   typeStr = "Rook";   break;
                case pieceType::queen:  typeStr = "Queen";  break;
                case pieceType::king:   typeStr = "King";   break;
                default: continue;
            }

            std::string key = colourStr + typeStr;
            sf::Sprite sprite(textures.at(key));

            auto textureSize = textures.at(key).getSize();
            sprite.setScale({squareSize/textureSize.x, squareSize/textureSize.y});
            sprite.setPosition({boardStartX + col * squareSize, boardStartY + row * squareSize});

            window.draw(sprite);
        }
    }
}
