## Repo for Uni chess project
# Funktionen

- **inBounds** Input: int i, int j
  I und J sind die Koordinaten(0-7) einer mögliche Postition auf dem Brett, die Funktionen entscheidet ob diese Position innerhalb dem Brett liegt.
- **lookFor**
- **isWhitePiece/isBlackPiece** Input: char board[8][8], char c, int i, int j
  board: das aktuelle Brett
  c: entscheiden ob wir weiß/schwarz suchen
  i, j: die Koordinaten des Königs
  Diese Funktion entscheidet ob die Figur "char c" den gegnerischen König "angreifen" kann. In diesem Fall return 1.
- **printBoard** Input: char board[8][8]
  Diese Funktion "print"-et das ganze Brett aus im Console.
- **checkBoardWhite/checkBoardBlack** Input: char board[8][8]
  board: das aktuelle Brett
  Diese Funktion entscheidet ob aktuell auf dem Brett der weiße/schwarze König sich gerade in Schach befindet
- **isCheck** Input: char board[8][8], bool isWhitesTurn
  board: das aktuelle Brett
  isWhitesTurn: bool falls true = weiß muss einen Zug machen, falls false = schwarz muss einen Zug machen
  Diese Funktion versucht zu entscheiden ob es Checkmate ist, aber es funktioniert nicht richtig..
- **moveWasMade** Input: char board[8][8], char piece, int sourceFile, int sourceRank, int targetFile, int targetRank,
  bool& isWhitesTurn, bool makeMove
  board: das aktuelle Brett
  piece: eine Figur mit der Funktion arbeiten soll
  sourceFile: die erste Koordinate der "piece" [die][]
  sourceRank: die zweite Koordinate der "piece" [][die]
  targetFile: die erste Koordinate der Figur die "angegriffen" wird [die][]
  targetRank: die zweite Koordinate der Figur die "angegriffen" wird [][die]
  isWhitesTurn: bool falls true = weiß muss einen Zug machen, falls false = schwarz muss einen Zug machen
  makeMove: diese Funktion entscheidet ob ein Zug möglich ist oder nicht, diese Variable entscheidet ob Zug in der Realität auf dem Brett gemacht werden soll oder nicht.
  Diese Funktion wie erwähnt entscheidet ob ein Zug möglich ist oder nicht und als Nebeneffekt führt den aus falls makeMove=true ist.
