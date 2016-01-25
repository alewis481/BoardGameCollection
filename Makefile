#TODO: Learn how to make better Makefiles 
compile all: driver.o reversi.o tictactoe.o life.o board.o player.o board_game.o coordinate.o
	g++ -std=c++11 -Wall -lncurses driver.o reversi.o tictactoe.o life.o board.o player.o board_game.o coordinate.o -o game_collection.out

driver.o: driver.cpp
	g++ -std=c++11 -Wall -c driver.cpp

reversi.o: reversi.cpp
	g++ -std=c++11 -Wall -c reversi.cpp

tictactoe.o: tictactoe.cpp
	g++ -std=c++11 -Wall -c tictactoe.cpp

life.o: life.cpp
	g++ -std=c++11 -Wall -c life.cpp

board.o: board.cpp
	g++ -std=c++11 -Wall -c board.cpp

player.o: player.cpp
	g++ -std=c++11 -Wall -c player.cpp

board_game.o: board_game.cpp
	g++ -std=c++11 -Wall -c board_game.cpp

coordinate.o: coordinate.cpp
	g++ -std=c++11 -Wall -c coordinate.cpp


DATA = 

run: 
	./game_collection.out $(DATA)

clean:
	rm -rf *.o
	rm -f game_collection.out
	rm -f *~ *.h.gch *#


