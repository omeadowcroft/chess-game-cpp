#pragma once

#include <vector>
#include <utility>
#include "board.h"

std::vector<std::pair<int,int>> getLegalMoves(chessPiece board[8][8], int row, int col);
