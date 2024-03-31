#ifndef CHESS_H
#define CHESS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <list>

#define LENGTH 8
#define pawnBLACK 'p'
#define pawnWHITE 'P'
#define rookBLACK 'r'
#define rookWHITE 'R'
#define knightWHITE 'N'
#define knightBLACK 'n'
#define bishopBLACK 'b'
#define bishopWHITE 'B'
#define queenWHITE 'Q'
#define queenBLACK 'q'
#define kingBLACK 'k'
#define kingWHITE 'K'
#define SIMPLEMOVE 1
#define CAPTURE 2
#define NOTVALID 3

using namespace sf;

// Board represented as a 2d array
extern char board[8][8];
// Keeping track of whos turn it is. true=whites turn, false=blacks turn
extern bool isWhitesTurn;
// Variables for the visualisation
extern int sizeOfASquare, x, y;
// Keeping track of if there is a visualisation available
extern bool promotionAvailableWhite, promotionAvailableBlack;
// struct to keep track of exactly where promotion is available
extern struct {
    int x, y;
};
// Piece currently selected
extern char pieceSelected;
// sourceFile, sourceRank indicate where the selected piece is being moved from
// targetFile, targetRank indicate where the selected piece is being moved to
extern int sourceFile, sourceRank, targetFile, targetRank;
// variable so everyone knows when a move is being made
extern bool moveBeingMade;
// list to keep track of the visual aspect of the available moves
// list was chosen because it has a dynamic length and we dont know
// in advance how many possible move Sprites we will need
extern std::list<Sprite> availableMovesList;

bool inBounds(int i, int j);
bool lookFork(char board[][8], char c, int i, int j);
bool lookForb(char board[][8], char c, int i, int j);
bool lookForr(char board[][8], char c, int i, int j);
bool lookForq(char board[][8], char c, int i, int j);
bool lookForn(char board[][8], char c, int i, int j);
bool lookForp(char board[][8], char c, int i, int j);
bool isWhitePiece(char piece);
bool isBlackPiece(char piece);
void printBoard(char board[8][8]);
int checkBoardWhite(char board[8][8]);
int checkBoardBlack(char board[8][8]);
bool isCheck(char board[8][8], bool isWhitesTurn);
int moveWasMade(char board[8][8], char piece, int sourceFile, int sourceRank, int targetFile, int targetRank,
    bool& isWhitesTurn, bool makeMove);

#endif
