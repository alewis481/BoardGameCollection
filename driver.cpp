/** 
 *
 */

#include "tictactoe.h"
#include "reversi.h"
#include "life.h"

#include <iostream>
#include <string>
#include <assert.h>



//good ideas:
//numerical option press 1 for ttt 2 for reversi...
//selectpiece option in class



int main(int argc, char** argv) {

  std::cout << "Welcome to the game collection!\n";

  if(argc == 2) {
    //TODO: accept command-line arguments
  }
  
  std::string gameName = "";
  while (gameName != "ttt" && gameName != "reversi" && gameName != "life") {
    std::cout << "Pick a game (ttt, reversi, life): ";
    std::cin >> gameName;
  }

 
  if (gameName == "ttt") { 
    TicTacToe game{};
    game.play();
  }
  else if (gameName == "reversi") {
    Reversi game{};
    game.play();
  }
  else if (gameName == "life") {
    Life game{};
    game.play();
  }
  else
    //TODO: have user retype input..
    exit(-1);
  
  //TODO: ask again after game is over if they'd like to play again or play
  //different game. Make a quit option. 


}
