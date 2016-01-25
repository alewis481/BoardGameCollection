/** 
 *
 */

#include <iostream> 
#include <string>
#include <regex>

#include "board_game.h"



BoardGame::BoardGame() : game_board_{0, '-'} {}

BoardGame::BoardGame(int board_dimension, char default_grid_symbol) :
  game_board_{board_dimension, default_grid_symbol}
{reset();}

void BoardGame::printBoard() const {game_board_.printBoard();}

void BoardGame::reset() {
  game_board_.resetBoard();
}

Coordinate BoardGame::getCoordinateFromUser() {
  //(?digit+(space | ,)space?digit+)?
  std::regex valid_input_template{R"((\()?(\d+)(\s|,)(\s?)(\d+)(\))?)"};
  std::string input = "";
  std::smatch matches;
  while(!std::regex_match(input, matches, valid_input_template))  {
    std::cout << "Please enter a coordinate as \"(x,y)\" or \"x y\": ";
    std::getline(std::cin, input);
  }
  //converts the coordinate values to integers and stores them in x,y
  int x = std::stoi(matches.format("$2"));
  int y = std::stoi(matches.format("$5"));

  return Coordinate(x,y);
}



