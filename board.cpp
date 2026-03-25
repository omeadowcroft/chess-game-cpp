#include "board.h"

chessPiece board[8][8] = {
    // row 0 - black back row
    {
        {pieceType::rook,   colour::black},
        {pieceType::knight, colour::black},
        {pieceType::bishop, colour::black},
        {pieceType::queen,  colour::black},
        {pieceType::king,   colour::black},
        {pieceType::bishop, colour::black},
        {pieceType::knight, colour::black},
        {pieceType::rook,   colour::black},
    },
    // row 1 - black pawns
    {
        {pieceType::pawn, colour::black},
        {pieceType::pawn, colour::black},
        {pieceType::pawn, colour::black},
        {pieceType::pawn, colour::black},
        {pieceType::pawn, colour::black},
        {pieceType::pawn, colour::black},
        {pieceType::pawn, colour::black},
        {pieceType::pawn, colour::black},
    },
    // rows 2-5 - empty
    {}, {}, {}, {},
    // row 6 - white pawns
    {
        {pieceType::pawn, colour::white},
        {pieceType::pawn, colour::white},
        {pieceType::pawn, colour::white},
        {pieceType::pawn, colour::white},
        {pieceType::pawn, colour::white},
        {pieceType::pawn, colour::white},
        {pieceType::pawn, colour::white},
        {pieceType::pawn, colour::white},
    },
    // row 7 - white back row
    {
        {pieceType::rook,   colour::white},
        {pieceType::knight, colour::white},
        {pieceType::bishop, colour::white},
        {pieceType::queen,  colour::white},
        {pieceType::king,   colour::white},
        {pieceType::bishop, colour::white},
        {pieceType::knight, colour::white},
        {pieceType::rook,   colour::white},
    },
};
