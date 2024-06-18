#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <list>
#include "chess.h"


using namespace sf;

char board[8][8] = { {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
					 {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
					 {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
					 {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'} };
bool isWhitesTurn = true;

//Original variables
int  sizeOfASquare = 100, x, y;
bool promotionAvailableWhite = false, promotionAvailableBlack = false;
struct
{
    int x, y;
}promotionWhite, promotionBlack;

// Piece
char pieceSelected = ' ';
// Source file and rank
int sourceFile = -1;
int sourceRank = -1;
// Target file and rank
int targetFile = -1;
int targetRank = -1;
// moveBeingMade: False if valid move hasnt been initiated, true if valid move is in progress
bool moveBeingMade = false;

//List for available move <Sprite>-s
std::list<Sprite> availableMovesList;

bool isHoveringOverPromotionAvailableSquare(int posY, int posX, int promotionWhiteY, int promotionWhiteX, int sizeOfASquare) {
	return posY >= promotionWhiteY * sizeOfASquare && posY <= (promotionWhiteY + 1) * sizeOfASquare && posX >= promotionWhiteX * sizeOfASquare && posX <= (promotionWhiteX + 1) * sizeOfASquare ? true : false;
}
bool isInTopLeftCorner(int posX, int posY) {
	int xx = posX % 100, yy = posY % 100;
	return xx < 50 && yy < 50 && xx > 0 && yy > 0 ? true : false;
}
bool isInTopRightCorner(int posX, int posY) {
	int xx = posX % 100, yy = posY % 100;
	return xx > 50 && xx < 100 && yy < 50 && yy > 0 ? true : false;
}
bool isInBottomRightCorner(int posX, int posY) {
	int xx = posX % 100, yy = posY % 100;
	return xx > 50 && xx < 100 && yy>50 && yy < 100 ? true : false;
}
bool isInBottomLeftCorner(int posX, int posY) {
	int xx = posX % 100, yy = posY % 100;
	return xx < 50 && xx > 0 && yy > 50 && y < 100 ? true : false;
}
int main()
{
	// Creating the window that we will visualise chess in with the help of SFML
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess visualisation by Gergo Bakos");
	// Setting the application icon
	sf::Image icon;
	icon.loadFromFile("images/icon.png");
	window.setIcon(20, 20, icon.getPixelsPtr());
	//Loading all the textures we will be needing for the visual representation
    Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16;
    t1.loadFromFile("images/board.png");
    t2.loadFromFile("images/pawnBlack.png");
    t3.loadFromFile("images/pawnWhite.png");
    t4.loadFromFile("images/rookBlack.png");
    t5.loadFromFile("images/rookWhite.png");
    t6.loadFromFile("images/knightWhite.png");
    t7.loadFromFile("images/knightBlack.png");
    t8.loadFromFile("images/bishopBlack.png");
    t9.loadFromFile("images/bishopWhite.png");
    t10.loadFromFile("images/queenWhite.png");
    t11.loadFromFile("images/queenBlack.png");
    t12.loadFromFile("images/kingBlack.png");
    t13.loadFromFile("images/kingWhite.png");
    t14.loadFromFile("images/transformWhite.png");
    t15.loadFromFile("images/transformBlack.png");
    t16.loadFromFile("images/circle.png");
	// In SFML we use Sprite-s to represent textures in the application
    Sprite table(t1);
    Sprite pawnBlack(t2);
    Sprite pawnWhite(t3);
    Sprite rookBlack(t4);
    Sprite rookWhite(t5);
    Sprite knightWhite(t6);
    Sprite knightBlack(t7);
    Sprite bishopBlack(t8);
    Sprite bishopWhite(t9);
    Sprite queenWhite(t10);
    Sprite queenBlack(t11);
    Sprite kingBlack(t12);
    Sprite kingWhite(t13);
    Sprite pieceBeingMovedSprite;
    Sprite promotionSymbolWhite(t14);
    Sprite promotionSymbolBlack(t15);
    Sprite availableMove(t16);
	// These 2 variables are needed for the draging mechanism
    float dx = 0, dy = 0;

    while (window.isOpen())
    {
        //Checking for window close
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
		//Getting the square the mouse is currently hovering over
        Vector2i pos = Mouse::getPosition(window);
        x = pos.x / sizeOfASquare;
        y = pos.y / sizeOfASquare;
		//Checking for a left click
        if (event.type == Event::MouseButtonPressed)
        {
            if (event.key.code == Mouse::Left)
            {
				// Checking if we are choosing a promotion
				if (promotionAvailableWhite)
				{
					if (isHoveringOverPromotionAvailableSquare(pos.y, pos.x, promotionWhite.y, promotionWhite.x, sizeOfASquare))
					{
						// We check where the player is clicking inside of the promotion square
						if (isInTopLeftCorner(pos.x, pos.y))
						{
							board[promotionWhite.y][promotionWhite.x] = rookWHITE;
							promotionAvailableWhite = false;
						}
						if (isInTopRightCorner(pos.x, pos.y))
						{
							board[promotionWhite.y][promotionWhite.x] = queenWHITE;
							promotionAvailableWhite = false;
						}
						if (isInBottomRightCorner(pos.x, pos.y))
						{
							board[promotionWhite.y][promotionWhite.x] = knightWHITE;
							promotionAvailableWhite = false;
						}
						if (isInBottomLeftCorner(pos.x, pos.y))
						{
							board[promotionWhite.y][promotionWhite.x] = bishopWHITE;
							promotionAvailableWhite = false;
						}
					}
				}
				if (promotionAvailableBlack)
				{
					if (isHoveringOverPromotionAvailableSquare(pos.y, pos.x, promotionBlack.y, promotionBlack.x, sizeOfASquare))
					{
						// We check where the player is clicking inside of the promotion square
						if (isInTopLeftCorner(pos.x, pos.y))
						{
							board[promotionBlack.y][promotionBlack.x] = rookBLACK;
							promotionAvailableBlack = false;
						}
						if (isInTopRightCorner(pos.x, pos.y))
						{
							board[promotionBlack.y][promotionBlack.x] = queenBLACK;
							promotionAvailableBlack = false;
						}
						if (isInBottomRightCorner(pos.x, pos.y))
						{
							board[promotionBlack.y][promotionBlack.x] = knightBLACK;
							promotionAvailableBlack = false;
						}
						if (isInBottomLeftCorner(pos.x, pos.y))
						{
							board[promotionBlack.y][promotionBlack.x] = bishopBLACK;
							promotionAvailableBlack = false;
						}
					}
				}
                // Choosing a piece to move
                if (board[y][x] != ' ')
				{
                    // dx,dy: For calculating the move visualisation
					dx = pos.x - x * 100;
					dy = pos.y - y * 100;
					// Choosing an available piece
					if (board[y][x] == pawnBLACK && isWhitesTurn == false)
					{
                        pieceSelected = pawnBLACK;
						pieceBeingMovedSprite = pawnBlack;
                        moveBeingMade = true;
                        sourceFile = x;
                        sourceRank = y;
						board[y][x] = ' ';
					}
					else if (board[y][x] == pawnWHITE && isWhitesTurn == true)
					{
                        pieceSelected = pawnWHITE;
						pieceBeingMovedSprite = pawnWhite;
                        moveBeingMade = true;
                        sourceFile = x;
                        sourceRank = y;
						board[y][x] = ' ';
                    }
					else if (board[y][x] == rookBLACK && isWhitesTurn == false)
					{
                        pieceSelected = rookBLACK;
						pieceBeingMovedSprite = rookBlack;
                        moveBeingMade = true;
                        sourceFile = x;
                        sourceRank = y;
						board[y][x] = ' ';
					}
					else if (board[y][x] == rookWHITE && isWhitesTurn == true)
					{
                        pieceSelected = rookWHITE;
						pieceBeingMovedSprite = rookWhite;
                        moveBeingMade = true;
                        sourceFile = x;
                        sourceRank = y;
						board[y][x] = ' ';
					}
					else if (board[y][x] == knightWHITE && isWhitesTurn == true)
					{
                        pieceSelected = knightWHITE;
						pieceBeingMovedSprite = knightWhite;
                        moveBeingMade = true;
                        sourceFile = x;
                        sourceRank = y;
						board[y][x] = ' ';
					}
					else if (board[y][x] == knightBLACK && isWhitesTurn == false)
					{
                        pieceSelected = knightBLACK;
						pieceBeingMovedSprite = knightBlack;
                        moveBeingMade = true;
                        sourceFile = x;
                        sourceRank = y;
						board[y][x] = ' ';
					}
					else if (board[y][x] == bishopBLACK && isWhitesTurn == false)
					{
                        pieceSelected = bishopBLACK;
						pieceBeingMovedSprite = bishopBlack;
                        moveBeingMade = true;
                        sourceFile = x;
                        sourceRank = y;
						board[y][x] = ' ';
					}
					else if (board[y][x] == bishopWHITE && isWhitesTurn == true)
					{
                        pieceSelected = bishopWHITE;
						pieceBeingMovedSprite = bishopWhite;
                        moveBeingMade = true;
                        sourceFile = x;
                        sourceRank = y;
						board[y][x] = ' ';
					}
					else if (board[y][x] == queenWHITE && isWhitesTurn == true)
					{
                        pieceSelected = queenWHITE;
						pieceBeingMovedSprite = queenWhite;
                        moveBeingMade = true;
                        sourceFile = x;
                        sourceRank = y;
						board[y][x] = ' ';
					}
					else if (board[y][x] == queenBLACK && isWhitesTurn == false)
					{
                        pieceSelected = queenBLACK;
						pieceBeingMovedSprite = queenBlack;
                        moveBeingMade = true;
                        sourceFile = x;
                        sourceRank = y;
						board[y][x] = ' ';
					}
					else if (board[y][x] == kingBLACK && isWhitesTurn == false)
					{
                        pieceSelected = kingBLACK;
						pieceBeingMovedSprite = kingBlack;
                        moveBeingMade = true;
                        sourceFile = x;
                        sourceRank = y;
						board[y][x] = ' ';
					}
					else if (board[y][x] == kingWHITE && isWhitesTurn == true)
					{
                        pieceSelected = kingWHITE;
						pieceBeingMovedSprite = kingWhite;
                        moveBeingMade = true;
                        sourceFile = x;
                        sourceRank = y;
						board[y][x] = ' ';
					}
				}
            }
        }
        // Available move Visualisation
        if (moveBeingMade)
        {
            for (int i = 0; i < LENGTH; i++)
            {
                for (int j = 0; j < LENGTH; j++)
                {
                    targetFile = j;
                    targetRank = i;
                    int result = moveWasMade(board, pieceSelected, sourceFile, sourceRank, targetFile, targetRank, isWhitesTurn, false);
                    if (result != NOTVALID) {
                        Sprite newSprite(t16);
                        newSprite.setPosition(j * sizeOfASquare, i * sizeOfASquare);
                        availableMovesList.push_back(newSprite);
                    }
                }
            }
        }
		//Checking for a release
		if (event.type == Event::MouseButtonReleased)
		{
			if (event.key.code == Mouse::Left)
			{
                if (moveBeingMade)
                {
                    targetFile = x;
                    targetRank = y;
                    //Checking if its a valid move
                    int result = moveWasMade(board, pieceSelected, sourceFile, sourceRank, targetFile, targetRank, isWhitesTurn, true);
                    if (result == 3) {
                        board[sourceRank][sourceFile] = pieceSelected;
                        std::cout << "Invalid move was made." << std::endl;
                        std::cout << "pieceSelected: " << pieceSelected << " sourceFile: " << sourceFile << " sourceRank: " << sourceRank << " targetFile: " << targetFile << " targetRank: " << targetRank << " isWhitesTurn: " << isWhitesTurn <<std::endl;
                    }
                    else {
                        // Play the sound 
						sf::SoundBuffer buffer;
						if (!buffer.loadFromFile("sounds/moveMade.wav")) {
							std::cerr << "Failed to load audio file." << std::endl;
						}
						sf::Sound sound;
						sound.setBuffer(buffer);
                        sound.play();
                        while (sound.getStatus() == sf::Sound::Playing) {}
                        //Checking for promotion
                        if (y == 0 && pieceSelected == pawnWHITE)
                        {
                            promotionAvailableWhite = true;
                            promotionWhite.x = x;
                            promotionWhite.y = y;
                            board[y][x] = 0;
                        }
                        if (y == 7 && pieceSelected == pawnBLACK)
                        {
                            promotionAvailableBlack = true;
                            promotionBlack.x = x;
                            promotionBlack.y = y;
                            board[y][x] = 0;
                        }
                    }         
                    moveBeingMade = 0;
                }
			}
		}
        // Display //
        window.clear();
        window.draw(table);
		// Drawing the promotion pieces
		if (promotionAvailableWhite == 1)
		{
			promotionSymbolWhite.setPosition(promotionWhite.x * sizeOfASquare, promotionWhite.y * sizeOfASquare);
			window.draw(promotionSymbolWhite);
		}
		if (promotionAvailableBlack == 1)
		{
			promotionSymbolBlack.setPosition(promotionBlack.x * sizeOfASquare, promotionBlack.y * sizeOfASquare);
			window.draw(promotionSymbolBlack);
		}
        if (moveBeingMade == true)
		{
			// Tracking the piece being moved to the cursor
			pieceBeingMovedSprite.setPosition(pos.x - dx, pos.y - dy);
			window.draw(pieceBeingMovedSprite);
			// Drawing a sprite on all the squares that are available for the player to move to
            for (Sprite sprite : availableMovesList) {
                window.draw(sprite);
            }
		}
        //Reset the available moves to empty once a player deselected a piece
        if (moveBeingMade == false)
        {
            availableMovesList = {};
        }
		//Drawing every piece on the board
		for (int i = 0; i < LENGTH; i++)
		{
			for (int j = 0; j < LENGTH; j++)
			{

				if (board[i][j] != 0)
				{
					if (board[i][j] == pawnBLACK)
					{
						pawnBlack.setPosition(j * sizeOfASquare, i * sizeOfASquare);
						window.draw(pawnBlack);
					}
					if (board[i][j] == pawnWHITE)
					{
						pawnWhite.setPosition(j * sizeOfASquare, i * sizeOfASquare);
						window.draw(pawnWhite);
					}
					if (board[i][j] == rookBLACK)
					{
						rookBlack.setPosition(j * sizeOfASquare, i * sizeOfASquare);
						window.draw(rookBlack);

					}
					if (board[i][j] == rookWHITE)
					{
						rookWhite.setPosition(j * sizeOfASquare, i * sizeOfASquare);
						window.draw(rookWhite);

					}
					if (board[i][j] == knightWHITE)
					{
						knightWhite.setPosition(j * sizeOfASquare, i * sizeOfASquare);
						window.draw(knightWhite);
					}
					if (board[i][j] == knightBLACK)
					{
						knightBlack.setPosition(j * sizeOfASquare, i * sizeOfASquare);
						window.draw(knightBlack);
					}
					if (board[i][j] == bishopBLACK)
					{
						bishopBlack.setPosition(j * sizeOfASquare, i * sizeOfASquare);
						window.draw(bishopBlack);
					}
					if (board[i][j] == bishopWHITE)
					{
						bishopWhite.setPosition(j * sizeOfASquare, i * sizeOfASquare);
						window.draw(bishopWhite);
					}
					if (board[i][j] == queenWHITE)
					{
						queenWhite.setPosition(j * sizeOfASquare, i * sizeOfASquare);
						window.draw(queenWhite);
					}
					if (board[i][j] == queenBLACK)
					{
						queenBlack.setPosition(j * sizeOfASquare, i * sizeOfASquare);
						window.draw(queenBlack);
					}
					if (board[i][j] == kingBLACK)
					{
						kingBlack.setPosition(j * sizeOfASquare, i * sizeOfASquare);
						window.draw(kingBlack);
					}
					if (board[i][j] == kingWHITE)
					{
						kingWhite.setPosition(j * sizeOfASquare, i * sizeOfASquare);
						window.draw(kingWhite);
					}
				}
			}
		}
        //Check for check
        if (((checkBoardBlack(board) == 2 && isWhitesTurn == true) ||
            (checkBoardWhite(board) == 1 && isWhitesTurn == false)) &&
            isCheck(board, isWhitesTurn)) {
			// Drawing a text on the board to indicate check
            // Declare and load a font
            sf::Font font;
            font.loadFromFile("fonts/SF-Pro-Text-Regular.otf");
            // Create a text
            sf::Text text("CHECK", font);
            text.setCharacterSize(50);
            text.setFillColor(sf::Color::Red);
			text.setPosition(0, 0);
            //text.setPosition(800 / 2.0f, 800 / 2.0f); //Window width divided by 2, same with height.
            //text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
            window.draw(text);
        }
        window.display();
    }
    
    return 0;
}