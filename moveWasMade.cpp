#include "chess.h"

bool areStartAndFinishSquaresDifferent(int sourceFile, int sourceRank, int targetFile, int targetRank) {
    return sourceFile == targetFile && sourceRank == targetRank ? false : true;
}
bool isTargetSquareEmpty(int targetFile, int targetRank) {
    return board[targetRank][targetFile] == ' ' ? true : false;
}
bool isWhitePawnSteppingOne(int sourceFile, int sourceRank, int targetFile, int targetRank) {
    return targetFile == sourceFile && targetRank == sourceRank - 1 ? true : false;
}
bool isBlackPawnSteppingOne(int sourceFile, int sourceRank, int targetFile, int targetRank) {
    return targetFile == sourceFile && targetRank == sourceRank + 1 ? true : false;
}
bool isTwoStepsWhitePawnStart(int sourceFile, int sourceRank, int targetFile, int targetRank) {
    return sourceRank == 6 && targetFile == sourceFile && targetRank == sourceRank - 2 &&
        board[sourceRank - 1][sourceFile] == ' ' ? true : false;
}
bool isTwoStepsBlackPawnStart(int sourceFile, int sourceRank, int targetFile, int targetRank) {
    return sourceRank == 1 && targetFile == sourceFile && targetRank == sourceRank + 2 &&
        board[sourceRank + 1][sourceFile] == ' ' ? true : false;
}
bool isDiagonalCaptureWhitePawn(int sourceFile, int sourceRank, int targetFile, int targetRank) {
    return (targetFile == sourceFile + 1 || targetFile == sourceFile - 1) && targetRank == sourceRank - 1 ? true : false;
} 
bool isDiagonalCaptureBlackPawn(int sourceFile, int sourceRank, int targetFile, int targetRank) {
    return (targetFile == sourceFile + 1 || targetFile == sourceFile - 1) && targetRank == sourceRank + 1 ? true : false;
} 
bool wouldTheWhiteKingBeInChess(char board[8][8], char piece, int sourceFile, int sourceRank, int targetFile, int targetRank, bool makeMove) {
    char tempBoard[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            tempBoard[i][j] = board[i][j];
        }
    }
    // Making the move
    tempBoard[sourceRank][sourceFile] = ' ';
    tempBoard[targetRank][targetFile] = piece;
    // Checking if it would result in the white King being in chess
    if (checkBoardBlack(tempBoard) != 2) {
        return false;  // Move forward one step
    }
    return true;
}
bool wouldTheBlackKingBeInChess(char board[8][8], char piece, int sourceFile, int sourceRank, int targetFile, int targetRank, bool makeMove) {
    char tempBoard[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            tempBoard[i][j] = board[i][j];
        }
    }
    // Making the move
    tempBoard[sourceRank][sourceFile] = ' ';
    tempBoard[targetRank][targetFile] = piece;
    // Checking if it would result in the white King being in chess
    if (checkBoardWhite(tempBoard) != 1) {
        return false;  // Move forward one step
    }
    return true;
}
int calculateFileDifference(int sourceFile, int targetFile) {
    return abs(targetFile - sourceFile);
}
int calculateRankDifference(int sourceRank, int targetRank) {
    return abs(targetRank - sourceRank);
}
bool isValidKnightMovePattern(int sourceFile, int sourceRank, int targetFile, int targetRank) {
    int fileDifference = calculateFileDifference(sourceFile, targetFile);
    int rankDifference = calculateRankDifference(sourceRank, targetRank);
    return (fileDifference == 2 && rankDifference == 1) || (fileDifference == 1 && rankDifference == 2);
}
bool isValidBishopMovePattern(int sourceFile, int sourceRank, int targetFile, int targetRank) {
    return std::abs(targetFile - sourceFile) == std::abs(targetRank - sourceRank) ? true : false;
}
int calculateBishopDirection(int target, int source) {
    return (target > source) ? 1 : -1;
}
bool isBishopsWayObstructed(char board[8][8], int sourceFile, int sourceRank, int targetFile, int targetRank) {
    int fileDirection = calculateBishopDirection(targetFile,sourceFile);
    int rankDirection = calculateBishopDirection(targetRank, sourceRank);
    for (int i = 1; i < std::abs(targetFile - sourceFile); ++i) {
        char pieceAtIntermediateSquare = board[sourceRank + i * rankDirection][sourceFile + i * fileDirection];
        if (pieceAtIntermediateSquare != ' ') 
            return true;
    }
    return false;
}
bool isValidHorizontalRookMovePattern(int sourceRank, int targetRank) {
    return (sourceRank == targetRank) ? true : false;
}
bool isValidVerticalRookMovePattern(int sourceFile, int targetFile) {
    return (sourceFile == targetFile) ? true : false;
}
bool isRooksWayVerticallyObstructed(char board[8][8], int sourceFile, int sourceRank, int targetFile, int targetRank) {
    // Check for obstacles along the vertical path
    int step = (sourceRank < targetRank) ? 1 : -1;
    for (int i = sourceRank + step; i != targetRank; i += step) {
        if (board[i][sourceFile] != ' ') {
            return true;  // Invalid move, obstacle in the path
        }
    }
    return false;
}
bool isRooksWayHorizontallyObstructed(char board[8][8], int sourceFile, int sourceRank, int targetFile, int targetRank) {
    // Check for obstacles along the horizontal path
    int step = (sourceFile < targetFile) ? 1 : -1;
    for (int i = sourceFile + step; i != targetFile; i += step) {
        if (board[sourceRank][i] != ' ') {
            return true;  // Invalid move, obstacle in the path
        }
    }
    return false;
}
bool isValidVerticalRookMove(char board[8][8], int sourceFile, int sourceRank, int targetFile, int targetRank) {
    return (isValidVerticalRookMovePattern(sourceFile, targetFile) && !isRooksWayVerticallyObstructed(board, sourceFile, sourceRank, targetFile, targetRank)) ? true : false;
}
bool isValidHorizontalRookMove(char board[8][8], int sourceFile, int sourceRank, int targetFile, int targetRank) {
    return (isValidHorizontalRookMovePattern(sourceRank, targetRank) && !isRooksWayHorizontallyObstructed(board, sourceFile, sourceRank, targetFile, targetRank)) ? true : false;
}
bool isValidRookMove(char board[8][8], int sourceFile, int sourceRank, int targetFile, int targetRank) {
    return (isValidHorizontalRookMove(board, sourceFile, sourceRank, targetFile, targetRank) || isValidVerticalRookMove(board, sourceFile, sourceRank, targetFile, targetRank)) ? true : false;
}
bool isValidQueenMovePattern(int sourceFile, int sourceRank, int targetFile, int targetRank) {
    return !(sourceFile != targetFile && sourceRank != targetRank && std::abs(sourceFile - targetFile) != std::abs(sourceRank - targetRank)) ? true : false;
}
bool isQueensWayObstructed(char board[8][8], int sourceFile, int sourceRank, int targetFile, int targetRank) {
    // Check for obstruction along the path (if any)
    int fileIncrement = (sourceFile < targetFile) ? 1 : (sourceFile > targetFile) ? -1 : 0;
    int rankIncrement = (sourceRank < targetRank) ? 1 : (sourceRank > targetRank) ? -1 : 0;

    for (int file = sourceFile + fileIncrement, rank = sourceRank + rankIncrement;
        file != targetFile || rank != targetRank; file += fileIncrement, rank += rankIncrement) {
        if (board[rank][file] != ' ') {
            return true;  // Invalid move, obstruction in the path
        }
    }
    return false;
}
bool isValidKingMovePattern(int sourceFile, int sourceRank, int targetFile, int targetRank) {
    // Calculate the absolute difference in file and rank
    int fileDiff = abs(targetFile - sourceFile);
    int rankDiff = abs(targetRank - sourceRank);
    if ((fileDiff == 1 && rankDiff == 0) ||  // Horizontal move
        (fileDiff == 0 && rankDiff == 1) ||  // Vertical move
        (fileDiff == 1 && rankDiff == 1))    // Diagonal move
        return true;
    return false;
}
int moveWasMade(char board[8][8], char piece, int sourceFile, int sourceRank, int targetFile, int targetRank,
    bool& isWhitesTurn, bool makeMove) {
    switch (piece) {
    // White pieces
    case pawnWHITE:
        if (!areStartAndFinishSquaresDifferent(sourceFile, sourceRank, targetFile, targetRank))
            return 3;
        if (isTargetSquareEmpty(targetFile, targetRank)) {
            if (isWhitePawnSteppingOne(sourceFile, sourceRank, targetFile, targetRank)) {
                if (!wouldTheWhiteKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                    if (makeMove) {
                        board[sourceRank][sourceFile] = ' ';
                        board[targetRank][targetFile] = piece;
                        isWhitesTurn = !isWhitesTurn;
                    }
                    return SIMPLEMOVE;
                }
            }
            else if (isTwoStepsWhitePawnStart(sourceFile, sourceRank, targetFile, targetRank)) {
                if (!wouldTheWhiteKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                    if (makeMove) {
                        board[sourceRank][sourceFile] = ' ';
                        board[targetRank][targetFile] = piece;
                        isWhitesTurn = !isWhitesTurn;
                    }
                    return SIMPLEMOVE;
                }
            }
        }
        else if (isDiagonalCaptureWhitePawn(sourceFile, sourceRank, targetFile, targetRank)) {
            if (islower(board[targetRank][targetFile])) {
                if (!wouldTheWhiteKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                    if (makeMove) {
                        board[sourceRank][sourceFile] = ' ';
                        board[targetRank][targetFile] = piece;
                        isWhitesTurn = !isWhitesTurn;
                    }
                    return CAPTURE;
                }
            }
        }
        else {
            return NOTVALID;
        }
        break;
    case knightWHITE:
        // Check if the source and target squares are different
        if (!areStartAndFinishSquaresDifferent(sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (isValidKnightMovePattern(sourceFile, sourceRank, targetFile, targetRank)) {
            if (isTargetSquareEmpty(targetFile, targetRank)) {
                if (!wouldTheWhiteKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                    if (makeMove) {
                        board[sourceRank][sourceFile] = ' ';
                        board[targetRank][targetFile] = piece;
                        isWhitesTurn = !isWhitesTurn;
                    }
                    return SIMPLEMOVE;
                }
            }
            else if (islower(board[targetRank][targetFile])) {
                if (!wouldTheWhiteKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                    if (makeMove) {
                        board[sourceRank][sourceFile] = ' ';
                        board[targetRank][targetFile] = piece;
                        isWhitesTurn = !isWhitesTurn;
                    }
                    return CAPTURE;
                }
            }
        }
        else {
            return NOTVALID;
        }
        break;
    case bishopWHITE:
        if (!areStartAndFinishSquaresDifferent(sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (!isValidBishopMovePattern(sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (isBishopsWayObstructed(board, sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (isTargetSquareEmpty(targetFile, targetRank)) {
            if (!wouldTheWhiteKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                if (makeMove) {
                    board[sourceRank][sourceFile] = ' ';
                    board[targetRank][targetFile] = piece;
                    isWhitesTurn = !isWhitesTurn;
                }
                return SIMPLEMOVE;
            }
        }
        else if (islower(board[targetRank][targetFile])) {
            if (!wouldTheWhiteKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                if (makeMove) {
                    board[sourceRank][sourceFile] = ' ';
                    board[targetRank][targetFile] = piece;
                    isWhitesTurn = !isWhitesTurn;
                }
                return CAPTURE;
            }
        } 
        else {
            return NOTVALID;
        }
        break;
    case rookWHITE:
        if (!areStartAndFinishSquaresDifferent(sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (!isValidRookMove(board, sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (isTargetSquareEmpty(targetFile, targetRank)) {
            if (!wouldTheWhiteKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                if (makeMove) {
                    board[sourceRank][sourceFile] = ' ';
                    board[targetRank][targetFile] = piece;
                    isWhitesTurn = !isWhitesTurn;
                }
                return SIMPLEMOVE;
            }
        }
        else if (islower(board[targetRank][targetFile])) {
            if (!wouldTheWhiteKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                if (makeMove) {
                    board[sourceRank][sourceFile] = ' ';
                    board[targetRank][targetFile] = piece;
                    isWhitesTurn = !isWhitesTurn;
                }
                return CAPTURE;
            }
        }
        else {
            return NOTVALID;
        }
        break;
    case queenWHITE:
        if (!areStartAndFinishSquaresDifferent(sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (!isValidQueenMovePattern(sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;  // Invalid move, not along a file, rank, or diagonal
        if(isQueensWayObstructed(board, sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (isTargetSquareEmpty(targetFile, targetRank)) {
            if (!wouldTheWhiteKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                if (makeMove) {
                    board[sourceRank][sourceFile] = ' ';
                    board[targetRank][targetFile] = piece;
                    isWhitesTurn = !isWhitesTurn;
                }
                return SIMPLEMOVE;
            }
        }
        else if (islower(board[targetRank][targetFile])) {
            if (!wouldTheWhiteKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                if (makeMove) {
                    board[sourceRank][sourceFile] = ' ';
                    board[targetRank][targetFile] = piece;
                    isWhitesTurn = !isWhitesTurn;
                }
                return CAPTURE;
            }
        }
        else {
            return NOTVALID;
        }
        break;
    case kingWHITE:
        if (!areStartAndFinishSquaresDifferent(sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (!isValidKingMovePattern(sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (isTargetSquareEmpty(targetFile, targetRank)) {
            if (!wouldTheWhiteKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                if (makeMove) {
                    board[sourceRank][sourceFile] = ' ';
                    board[targetRank][targetFile] = piece;
                    isWhitesTurn = !isWhitesTurn;
                }
                return SIMPLEMOVE;
            }
        }
        else if (islower(board[targetRank][targetFile])) {
            if (!wouldTheWhiteKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                if (makeMove) {
                    board[sourceRank][sourceFile] = ' ';
                    board[targetRank][targetFile] = piece;
                    isWhitesTurn = !isWhitesTurn;
                }
                return CAPTURE;
            }
        }
        else {
            return NOTVALID;
        }
        break;
    // Black pieces
    case pawnBLACK:
        if (!areStartAndFinishSquaresDifferent(sourceFile, sourceRank, targetFile, targetRank))
            return 3;
        if (isTargetSquareEmpty(targetFile, targetRank)) {
            if (isBlackPawnSteppingOne(sourceFile, sourceRank, targetFile, targetRank)) {
                if (!wouldTheBlackKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                    if (makeMove) {
                        board[sourceRank][sourceFile] = ' ';
                        board[targetRank][targetFile] = piece;
                        isWhitesTurn = !isWhitesTurn;
                    }
                    return SIMPLEMOVE;
                }
            }
            else if (isTwoStepsBlackPawnStart(sourceFile, sourceRank, targetFile, targetRank)) {
                if (!wouldTheBlackKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                    if (makeMove) {
                        board[sourceRank][sourceFile] = ' ';
                        board[targetRank][targetFile] = piece;
                        isWhitesTurn = !isWhitesTurn;
                    }
                    return SIMPLEMOVE;
                }
            }
        }
        else if (isDiagonalCaptureBlackPawn(sourceFile, sourceRank, targetFile, targetRank)) {
            if (isupper(board[targetRank][targetFile])) {
                if (!wouldTheBlackKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                    if (makeMove) {
                        board[sourceRank][sourceFile] = ' ';
                        board[targetRank][targetFile] = piece;
                        isWhitesTurn = !isWhitesTurn;
                    }
                    return CAPTURE;
                }
            }
        }
        else {
            return NOTVALID;
        }
        break;
    case knightBLACK:
        if (!areStartAndFinishSquaresDifferent(sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (isValidKnightMovePattern(sourceFile, sourceRank, targetFile, targetRank)) {
            if (isTargetSquareEmpty(targetFile, targetRank)) {
                if (!wouldTheBlackKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                    if (makeMove) {
                        board[sourceRank][sourceFile] = ' ';
                        board[targetRank][targetFile] = piece;
                        isWhitesTurn = !isWhitesTurn;
                    }
                    return SIMPLEMOVE;
                }
            }
            else if (isupper(board[targetRank][targetFile])) {
                if (!wouldTheBlackKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                    if (makeMove) {
                        board[sourceRank][sourceFile] = ' ';
                        board[targetRank][targetFile] = piece;
                        isWhitesTurn = !isWhitesTurn;
                    }
                    return CAPTURE;
                }
            }
        }
        else {
            return NOTVALID;
        }
        break;
    case bishopBLACK:
        if (!areStartAndFinishSquaresDifferent(sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (!isValidBishopMovePattern(sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (isBishopsWayObstructed(board, sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (isTargetSquareEmpty(targetFile, targetRank)) {
            if (!wouldTheBlackKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                if (makeMove) {
                    board[sourceRank][sourceFile] = ' ';
                    board[targetRank][targetFile] = piece;
                    isWhitesTurn = !isWhitesTurn;
                }
                return SIMPLEMOVE;
            }
        }
        else if (isupper(board[targetRank][targetFile])) {
            if (!wouldTheBlackKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                if (makeMove) {
                    board[sourceRank][sourceFile] = ' ';
                    board[targetRank][targetFile] = piece;
                    isWhitesTurn = !isWhitesTurn;
                }
                return CAPTURE;
            }
        }
        else {
            return NOTVALID;
        }
        break;
    case rookBLACK:
        if (!areStartAndFinishSquaresDifferent(sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (!isValidRookMove(board, sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (isTargetSquareEmpty(targetFile, targetRank)) {
            if (!wouldTheBlackKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                if (makeMove) {
                    board[sourceRank][sourceFile] = ' ';
                    board[targetRank][targetFile] = piece;
                    isWhitesTurn = !isWhitesTurn;
                }
                return SIMPLEMOVE;
            }
        }
        else if (isupper(board[targetRank][targetFile])) {
            if (!wouldTheBlackKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                if (makeMove) {
                    board[sourceRank][sourceFile] = ' ';
                    board[targetRank][targetFile] = piece;
                    isWhitesTurn = !isWhitesTurn;
                }
                return CAPTURE;
            }
        }
        else {
            return NOTVALID;
        }
        break;
    case queenBLACK:
        if (!areStartAndFinishSquaresDifferent(sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (!isValidQueenMovePattern(sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;  // Invalid move, not along a file, rank, or diagonal
        if (isQueensWayObstructed(board, sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (isTargetSquareEmpty(targetFile, targetRank)) {
            if (!wouldTheBlackKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                if (makeMove) {
                    board[sourceRank][sourceFile] = ' ';
                    board[targetRank][targetFile] = piece;
                    isWhitesTurn = !isWhitesTurn;
                }
                return SIMPLEMOVE;
            }
        }
        else if (isupper(board[targetRank][targetFile])) {
            if (!wouldTheBlackKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                if (makeMove) {
                    board[sourceRank][sourceFile] = ' ';
                    board[targetRank][targetFile] = piece;
                    isWhitesTurn = !isWhitesTurn;
                }
                return CAPTURE;
            }
        }
        else {
            return NOTVALID;
        }
        break;
    case kingBLACK:
        if (!areStartAndFinishSquaresDifferent(sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (!isValidKingMovePattern(sourceFile, sourceRank, targetFile, targetRank))
            return NOTVALID;
        if (isTargetSquareEmpty(targetFile, targetRank)) {
            if (!wouldTheBlackKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                if (makeMove) {
                    board[sourceRank][sourceFile] = ' ';
                    board[targetRank][targetFile] = piece;
                    isWhitesTurn = !isWhitesTurn;
                }
                return SIMPLEMOVE;
            }
        }
        else if (isupper(board[targetRank][targetFile])) {
            if (!wouldTheBlackKingBeInChess(board, piece, sourceFile, sourceRank, targetFile, targetRank, makeMove)) {
                if (makeMove) {
                    board[sourceRank][sourceFile] = ' ';
                    board[targetRank][targetFile] = piece;
                    isWhitesTurn = !isWhitesTurn;
                }
                return CAPTURE;
            }
        }
        else {
            return NOTVALID;
        }
        break;
    }
    return 3;
}