#include "chess.h"

bool lookFork(char board[][8], char c, int i, int j) {
    // Store all possible moves
    // of the king
    int x[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int y[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int k = 0; k < 8; k++) {
        // incrementing index
        // values
        int m = i + x[k];
        int n = j + y[k];

        // checking boundary
        // conditions and
        // character match
        if (inBounds(m, n) && board[m][n] == c) return true;
    }
    return false;
}
bool lookForb(char board[][8], char c, int i, int j) {
    // Check the lower right diagonal
    int k = 0;
    while (inBounds(i + k + 1, j + k + 1)) {
        ++k;
        if (board[i + k][j + k] == c) return true;
        if (board[i + k][j + k] != ' ') break;
    }

    // Check the lower left diagonal
    k = 0;
    while (inBounds(i + k + 1, j - k - 1)) {
        ++k;
        if (board[i + k][j - k] == c) return true;
        if (board[i + k][j - k] != ' ') break;
    }

    // Check the upper right diagonal
    k = 0;
    while (inBounds(i - k - 1, j + k + 1)) {
        ++k;
        if (board[i - k][j + k] == c) return true;
        if (board[i - k][j + k] != ' ') break;
    }

    // Check the upper left diagonal
    k = 0;
    while (inBounds(i - k - 1, j - k - 1)) {
        ++k;
        if (board[i - k][j - k] == c) return true;
        if (board[i - k][j - k] != ' ') break;
    }

    return false;
}
bool lookForr(char board[][8], char c, int i, int j) {
    // Check downwards
    int k = 0;
    while (inBounds(i + ++k, j)) {
        if (board[i + k][j] == c) return true;
        if (board[i + k][j] != ' ') break;
    }

    // Check upwards
    k = 0;
    while (inBounds(i + --k, j)) {
        if (board[i + k][j] == c) return true;
        if (board[i + k][j] != ' ') break;
    }

    // Check right
    k = 0;
    while (inBounds(i, j + ++k)) {
        if (board[i][j + k] == c) return true;
        if (board[i][j + k] != ' ') break;
    }

    // Check left
    k = 0;
    while (inBounds(i, j + --k)) {
        if (board[i][j + k] == c) return true;
        if (board[i][j + k] != ' ') break;
    }
    return false;
}
bool lookForq(char board[][8], char c, int i, int j) {
    // Queen's moves are a combination
    // of both the Bishop and the Rook
    if (lookForb(board, c, i, j) || lookForr(board, c, i, j)) return true;

    return false;
}
bool lookForn(char board[][8], char c, int i, int j) {
    // All possible moves of
    // the knight
    int x[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
    int y[] = { 1, -1, 1, -1, 2, -2, 2, -2 };

    for (int k = 0; k < 8; k++) {
        // Incrementing index
        // values
        int m = i + x[k];
        int n = j + y[k];

        // Checking boundary conditions
        // and character match
        if (inBounds(m, n) && board[m][n] == c) return true;
    }
    return false;
}
bool lookForp(char board[][8], char c, int i, int j) {
    char lookFor;
    if (isupper(c)) {
        // Check for white pawn
        lookFor = 'P';
        if (inBounds(i + 1, j - 1) && board[i + 1][j - 1] == lookFor) return true;

        if (inBounds(i + 1, j + 1) && board[i + 1][j + 1] == lookFor) return true;
    }
    else {
        // Check for black pawn
        lookFor = 'p';
        if (inBounds(i - 1, j - 1) && board[i - 1][j - 1] == lookFor) return true;
        if (inBounds(i - 1, j + 1) && board[i - 1][j + 1] == lookFor) return true;
    }
    return false;
}