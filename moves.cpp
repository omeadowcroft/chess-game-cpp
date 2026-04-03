#include "moves.h"
#include <cstdlib>

static int sign(int x) { return (x > 0) - (x < 0); }

static std::pair<int,int> findKing(chessPiece board[8][8], colour c) {
    for (int r = 0; r < 8; r++)
        for (int col = 0; col < 8; col++)
            if (board[r][col].type == pieceType::king && board[r][col].pieceColour == c)
                return {r, col};
    return {-1, -1};
}

static std::vector<std::pair<int,int>> filterForPin(chessPiece board[8][8], int row, int col,
                                                     std::vector<std::pair<int,int>> moves) {
    colour own = board[row][col].pieceColour;
    auto [kingRow, kingCol] = findKing(board, own);

    int dRow = row - kingRow;
    int dCol = col - kingCol;

    // piece must be on the same rank, file, or diagonal as the king to be pinnable
    if (dRow != 0 && dCol != 0 && std::abs(dRow) != std::abs(dCol))
        return moves;

    int dr = sign(dRow);
    int dc = sign(dCol);

    // check nothing sits between king and this piece
    int r = kingRow + dr, c = kingCol + dc;
    while (r != row || c != col) {
        if (board[r][c].type != pieceType::none)
            return moves;
        r += dr; c += dc;
    }

    // walk past the piece looking for a pinning attacker
    r = row + dr; c = col + dc;
    while (r >= 0 && r < 8 && c >= 0 && c < 8) {
        if (board[r][c].type != pieceType::none) {
            if (board[r][c].pieceColour == own) break;

            pieceType t = board[r][c].type;
            bool diagonal = (dr != 0 && dc != 0);
            bool canPin = diagonal ? (t == pieceType::bishop || t == pieceType::queen)
                                   : (t == pieceType::rook   || t == pieceType::queen);
            if (!canPin) break;

            // pinned — keep only moves that stay on the ray (including capturing the attacker)
            std::vector<std::pair<int,int>> ray;
            int pr = kingRow + dr, pc = kingCol + dc;
            while (pr != r + dr || pc != c + dc) {
                ray.push_back({pr, pc});
                pr += dr; pc += dc;
            }

            std::vector<std::pair<int,int>> filtered;
            for (auto& m : moves)
                for (auto& p : ray)
                    if (m == p) { filtered.push_back(m); break; }
            return filtered;
        }
        r += dr; c += dc;
    }

    return moves;
}

static void addSlidingMoves(chessPiece board[8][8], int row, int col,
                             std::initializer_list<std::pair<int,int>> dirs,
                             std::vector<std::pair<int,int>>& moves) {
    colour own = board[row][col].pieceColour;
    for (auto [dr, dc] : dirs) {
        int r = row + dr, c = col + dc;
        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            if (board[r][c].type != pieceType::none) {
                if (board[r][c].pieceColour != own)
                    moves.push_back({r, c});
                break;
            }
            moves.push_back({r, c});
            r += dr; c += dc;
        }
    }
}

static std::vector<std::pair<int,int>> getPawnMoves(chessPiece board[8][8], int row, int col) {
    std::vector<std::pair<int,int>> moves;
    chessPiece& pawn = board[row][col];
    int dir = (pawn.pieceColour == colour::white) ? -1 : 1;
    int startRow = (pawn.pieceColour == colour::white) ? 6 : 1;
    int forwardRow = row + dir;

    if (forwardRow >= 0 && forwardRow < 8 && board[forwardRow][col].type == pieceType::none) {
        moves.push_back({forwardRow, col});
        if (row == startRow) {
            int twoRow = row + 2 * dir;
            if (board[twoRow][col].type == pieceType::none)
                moves.push_back({twoRow, col});
        }
    }

    for (int dcol : {-1, 1}) {
        int captureCol = col + dcol;
        if (captureCol >= 0 && captureCol < 8 && forwardRow >= 0 && forwardRow < 8) {
            chessPiece& target = board[forwardRow][captureCol];
            if (target.type != pieceType::none && target.pieceColour != pawn.pieceColour)
                moves.push_back({forwardRow, captureCol});
        }
    }

    return moves;
}

static std::vector<std::pair<int,int>> getKnightMoves(chessPiece board[8][8], int row, int col) {
    std::vector<std::pair<int,int>> moves;
    colour own = board[row][col].pieceColour;
    for (auto [dr, dc] : std::initializer_list<std::pair<int,int>>{{-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1}}) {
        int r = row + dr, c = col + dc;
        if (r >= 0 && r < 8 && c >= 0 && c < 8)
            if (board[r][c].type == pieceType::none || board[r][c].pieceColour != own)
                moves.push_back({r, c});
    }
    return moves;
}

static std::vector<std::pair<int,int>> getBishopMoves(chessPiece board[8][8], int row, int col) {
    std::vector<std::pair<int,int>> moves;
    addSlidingMoves(board, row, col, {{-1,-1},{-1,1},{1,-1},{1,1}}, moves);
    return moves;
}

static std::vector<std::pair<int,int>> getRookMoves(chessPiece board[8][8], int row, int col) {
    std::vector<std::pair<int,int>> moves;
    addSlidingMoves(board, row, col, {{-1,0},{1,0},{0,-1},{0,1}}, moves);
    return moves;
}

static std::vector<std::pair<int,int>> getQueenMoves(chessPiece board[8][8], int row, int col) {
    std::vector<std::pair<int,int>> moves;
    addSlidingMoves(board, row, col, {{-1,-1},{-1,1},{1,-1},{1,1},{-1,0},{1,0},{0,-1},{0,1}}, moves);
    return moves;
}

static std::vector<std::pair<int,int>> getKingMoves(chessPiece board[8][8], int row, int col) {
    std::vector<std::pair<int,int>> moves;
    colour own = board[row][col].pieceColour;
    for (auto [dr, dc] : std::initializer_list<std::pair<int,int>>{{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}}) {
        int r = row + dr, c = col + dc;
        if (r >= 0 && r < 8 && c >= 0 && c < 8)
            if (board[r][c].type == pieceType::none || board[r][c].pieceColour != own)
                moves.push_back({r, c});
    }
    return moves;
}

std::vector<std::pair<int,int>> getLegalMoves(chessPiece board[8][8], int row, int col) {
    switch (board[row][col].type) {
        case pieceType::pawn:   return filterForPin(board, row, col, getPawnMoves(board, row, col));
        case pieceType::knight: return filterForPin(board, row, col, getKnightMoves(board, row, col));
        case pieceType::bishop: return filterForPin(board, row, col, getBishopMoves(board, row, col));
        case pieceType::rook:   return filterForPin(board, row, col, getRookMoves(board, row, col));
        case pieceType::queen:  return filterForPin(board, row, col, getQueenMoves(board, row, col));
        case pieceType::king:   return getKingMoves(board, row, col);
        default:                return {};
    }
}
