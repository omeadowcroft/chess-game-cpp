#pragma once

enum class pieceType { none, pawn, knight, bishop, rook, queen, king };
enum class colour { white, black };

struct chessPiece {
    pieceType type;
    colour pieceColour;
};

extern chessPiece board[8][8];
