#include "chess.h"

bool isCheck(char board[8][8], bool isWhitesTurn) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] == ' ') {
            }
            else if (isWhitesTurn && isWhitePiece(board[i][j])) {
                for (int x = 0; x < 8; ++x) {
                    for (int y = 0; y < 8; ++y) {
                        if (isBlackPiece(board[x][y])) {
                            int result = moveWasMade(board, board[i][j], i, j, x, y, isWhitesTurn, false);
                            if (result != 3) {
                                return false;
                            }
                        }
                    }
                }
            }
            else if (isWhitesTurn == false && isBlackPiece(board[i][j])) {
                for (int x = 0; x < 8; ++x) {
                    for (int y = 0; y < 8; ++y) {
                        if (isWhitePiece(board[x][y])) {
                            int result = moveWasMade(board, board[i][j], i, j, x, y, isWhitesTurn, false);
                            if (result != 3) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}
