#include "chess.h"

int checkBoardWhite(char board[8][8]) {
    // Find the position of both
    // the kings
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Check for all pieces which
            // can attack White King
            if (board[i][j] == 'k') {
                // Check for Knight
                if (lookForn(board, 'N', i, j)) {
                    // std::cout << "lookForn";
                    return 1;
                }

                // Check for Pawn
                if (lookForp(board, 'P', i, j)) {
                    // std::cout << "lookForp";
                    return 1;
                }

                // Check for Rook
                if (lookForr(board, 'R', i, j)) {
                    // std::cout << "lookForr";
                    return 1;
                }

                // Check for Bishop
                if (lookForb(board, 'B', i, j)) {
                    // std::cout << "lookForb";
                    return 1;
                }

                // Check for Queen
                if (lookForq(board, 'Q', i, j)) {
                    // std::cout << "lookForq";
                    return 1;
                }

                // Check for King
                if (lookFork(board, 'K', i, j)) {
                    // std::cout << "lookFork";
                    return 1;
                }
            }
        }
    }
    return 0;
}
int checkBoardBlack(char board[8][8]) {
    // Find the position of both
    // the kings
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Check for all pieces which
            // can attack Black King
            if (board[i][j] == 'K') {
                // Check for Knight
                if (lookForn(board, 'n', i, j)) return 2;

                // Check for Pawn
                if (lookForp(board, 'p', i, j)) return 2;

                // Check for Rook
                if (lookForr(board, 'r', i, j)) return 2;

                // Check for Bishop
                if (lookForb(board, 'b', i, j)) return 2;

                // Check for Queen
                if (lookForq(board, 'q', i, j)) return 2;

                // Check for King
                if (lookFork(board, 'k', i, j)) return 2;
            }
        }
    }
    return 0;
}