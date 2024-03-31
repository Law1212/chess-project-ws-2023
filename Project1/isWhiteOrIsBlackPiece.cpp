#include "chess.h"

bool isWhitePiece(char piece) {
    return (piece == 'P' || piece == 'N' || piece == 'B' || piece == 'R' || piece == 'Q' || piece == 'K');
}
bool isBlackPiece(char piece) {
    return (piece == 'p' || piece == 'n' || piece == 'b' || piece == 'r' || piece == 'q' || piece == 'k');
}