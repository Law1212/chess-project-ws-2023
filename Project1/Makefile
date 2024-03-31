LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-sound
CXX := g++

all: thegame

%.o: %.cpp %.hpp
    $(CXX) -c $< -o $@

thegame: main.o moveWasMade.o printBoard.o lookFor.o isWhiteOrIsBlackPiece.o isCheckMate.o inBounds.o checkForKingCheck.o
    @echo "** Building the game"
    $(CXX) -o thegame $^ $(LIBS)

clean:
    @echo "** Removing object files and executable..."
    rm -f *.o thegame