#include <tuple>     //  for tuple
#include <iostream>  //  for cout
#include <algorithm> //  for max

#include "reversi.h"

//TODO: replace magic number
Reversi::Reversi() : BoardGame(8), player_list_{Player('X'), Player('O')}
    {reset();}

//board dimension is always at least 1
Reversi::Reversi(int board_dimension) : BoardGame(std::max(board_dimension,1)),
					player_list_{Player('X'), Player('O')}
    {reset();}


void Reversi::reset() {
  BoardGame::reset();
  //sets up base moves on the board, 2 of each player symbols in the center
  game_board_.setSymbol(Coordinate(3,3), player_list_[0].getSymbol());
  game_board_.setSymbol(Coordinate(4,4), player_list_[0].getSymbol());
  
  game_board_.setSymbol(Coordinate(3,4), player_list_[1].getSymbol());
  game_board_.setSymbol(Coordinate(4,3), player_list_[1].getSymbol());
}

bool Reversi::flip(Coordinate pos, int dx, int dy, bool valid, char symbol) {
  //if next move is not on board, then not valid
  if (!game_board_.isInBounds(pos))
    return false;
  //if so far not valid, but next piece is self, flip preceding pieces
  if (!valid && game_board_.getSymbol(pos) == symbol)
    return true;
  else if(!valid && game_board_.getSymbol(pos) !=game_board_.getDefaultSymbol())
    valid = flip(Coordinate(pos.row+dx, pos.col+dy), dx, dy, valid, symbol);
  
  if(valid) {
    std::cout << "symbol is " << symbol << "\n";
    game_board_.setSymbol(pos, symbol);
    return true;
  }
  else
    return false;
  
}

int Reversi::numPlayers() const {return player_list_.size();}

void Reversi::doMove(Coordinate pos, char symbol) {
  
  if(game_board_.isInBounds(pos) && isLegalMove(pos, symbol)) {
    game_board_.setSymbol(pos, symbol);
    flipAdjacent(pos, symbol);
  }
}

void Reversi::flipAdjacent(Coordinate pos, char symbol) {
  //use islegalmove to determine if move can be made
  //  if (!isLegalMove(pos, symbol)) {
  // return;
  // }
  
  //consider replacing this with some check adjacent thing?
  //maybe returns a vector of same symbol adjacent?
  Coordinate top_left(pos.row - 1, pos.col - 1);
  Coordinate top(pos.row - 1, pos.col);
  Coordinate top_right(pos.row - 1, pos.col + 1);
  Coordinate right(pos.row, pos.col + 1);
  Coordinate bottom_right(pos.row + 1, pos.col + 1);
  Coordinate bottom(pos.row + 1, pos.col);
  Coordinate bottom_left(pos.row + 1, pos.col - 1);
  Coordinate left(pos.row, pos.col - 1);
  
  using vectorOfTriples = std::vector<std::tuple<Coordinate, int, int>>;

  //makes a vector storing each adjacent position relative to pos
  //the second two ints are the direction of the position relative to pos
  vectorOfTriples adjacent = {std::make_tuple(top_left , -1, -1),
			      std::make_tuple(top, -1, 0),
			      std::make_tuple(top_right , -1, 1),
			      std::make_tuple(right, 0, 1),
			      std::make_tuple(bottom_right, 1, 1),
			      std::make_tuple(bottom, 1, 0),
			      std::make_tuple(bottom_left , 1, -1),
			      std::make_tuple(left, 0, -1) };
  
  
  //use flip to flip all necessary pieces
  for(auto x : adjacent) {
    //    coordinate     dx              dy           initially player
    flip(std::get<0>(x), std::get<1>(x), std::get<2>(x), false, symbol);
      }
  
  
}


bool Reversi::isDone() const {

  int player1_available_moves = 0;
  int player2_available_moves = 0;
  //counts the number of moves possible for each player
  for (int row = 0; row < game_board_.dimension(); ++row) {
    for (int col = 0; col < game_board_.dimension(); ++col) {
      if (isLegalMove(Coordinate(row, col), player_list_[0].getSymbol()))
	++player1_available_moves;
      if (isLegalMove(Coordinate(row ,col), player_list_[1].getSymbol()))
	++player2_available_moves;
    }
  }
  //game is over if a player cannot make any moves
  //TODO: make sure this is correct gameplay
  if(player1_available_moves == 0 || player2_available_moves == 0)
    return true;
  else
    return false;
}

//recursive function to determine whether path in some direction is valid
//used in isLegalMove()
bool Reversi::isValidPath(Coordinate pos, int dx, int dy, bool valid, char sym) const {

  //if next move is not on board, then not valid
  if (!game_board_.isInBounds(pos))
    return false;
  //if so far not valid, but next piece is self, flip preceding pieces
  if (!valid && game_board_.getSymbol(pos) == sym)
    return true;
  else if(!valid && game_board_.getSymbol(pos) !=game_board_.getDefaultSymbol())
    valid =isValidPath(Coordinate(pos.row+dx, pos.col+dy), dx, dy, valid, sym);
  
  return valid;
}


bool Reversi::isLegalMove(Coordinate pos, char sym) const {
  if(game_board_.isOccupied(pos))
    return false;
  
  //consider replacing this with some check adjacent thing?
  //maybe returns a vector of same symbol adjacent?
  Coordinate top_left(pos.row - 1, pos.col - 1);
  Coordinate top(pos.row - 1, pos.col);
  Coordinate top_right(pos.row - 1, pos.col + 1);
  Coordinate right(pos.row, pos.col + 1);
  Coordinate bottom_right(pos.row + 1, pos.col + 1);
  Coordinate bottom(pos.row + 1, pos.col);
  Coordinate bottom_left(pos.row + 1, pos.col - 1);
  Coordinate left(pos.row, pos.col - 1);

  //used to define paths from position in each direction
  //the second two ints specify direction 
  using vectorOfTriples = std::vector<std::tuple<Coordinate, int, int>>;

  //TODO: replace magic numbers
  vectorOfTriples adjacent = {std::make_tuple(top_left , -1, -1),
			      std::make_tuple(top, -1, 0),
			      std::make_tuple(top_right , -1, 1),
			      std::make_tuple(right, 0, 1),
			      std::make_tuple(bottom_right, 1, 1),
			      std::make_tuple(bottom, 1, 0),
			      std::make_tuple(bottom_left , 1, -1),
			      std::make_tuple(left, 0, -1) };
  
  for (auto x : adjacent) {
    //if not out of bounds, not same symbol, not default symbol, and if
    //path of opposite symbols leads to same symbol, return true
    //TODO:typedef the std::gets to something more readable
    if (game_board_.isInBounds(std::get<0>(x))
	&& game_board_.getSymbol(std::get<0>(x))!=game_board_.getDefaultSymbol()
	&& game_board_.getSymbol(std::get<0>(x)) != sym
	&& isValidPath(std::get<0>(x),std::get<1>(x),std::get<2>(x),false,sym)){
      return true;
    }
  }
  return false;
  
}

void Reversi::results() const {
  //holds number of symbols on the board for each player
  int counter_player1 = 0;
  int counter_player2 = 0;

  //count number of symbols on board
  //whoever has the most symbols on the board wins
  for (int row = 0; row < game_board_.dimension(); ++row) {
    for (int col = 0; col < game_board_.dimension(); ++col) {
      if(game_board_.getSymbol(Coordinate(row, col))
	 == player_list_[0].getSymbol()) {
	++counter_player1;
      }
      else if(game_board_.getSymbol(Coordinate(row, col))
	      == player_list_[1].getSymbol()) {
	++counter_player2;
      }
    }
  }
  
  if(counter_player1 == counter_player2)
    std::cout << "Game over. The game was a draw!\n";
  else if (counter_player1 > counter_player2)
    std::cout << "Game over. Player 1 wins!\n";
  else
    std::cout << "Game over. Player 2 wins!\n";
}


void Reversi::play() {
  //holds index of player in player vector, starts at 0 for player 1
  int current_player = 0;
  
  reset();
  printBoard();

  while(!isDone()) {
    std::cout << "Player " << current_player + 1 << "'s turn. \n";
    Coordinate nextMove(getCoordinateFromUser());
    while(!isLegalMove(nextMove, player_list_[current_player].getSymbol())) {
      std::cout << "Invalid move. Please try again.\n";
      nextMove = getCoordinateFromUser();
    }
    doMove(nextMove, player_list_[current_player].getSymbol());
    printBoard();

    if(current_player == 0)
      current_player = 1;
    else
      current_player = 0;
  }
  results();
  
}
