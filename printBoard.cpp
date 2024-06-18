#include "chess.h"

void printBoard(char board[8][8]) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::cout << board[i][j];
        }
        std::cout << std::endl;
    }
}