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
  
  //use flip to flip all necessary pieces
  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      if(dx || dy) {
	flip(Coordinate(pos.row+dx, pos.col+dy), dx, dy, false, symbol);
      }
    }
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
  return player1_available_moves == 0 || player2_available_moves == 0;

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
  
  //if not out of bounds, not same symbol, not default symbol, and if
  //path of opposite symbols leads to same symbol, return true
  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      Coordinate adjacent {pos.row + dx, pos.col + dy};
      if ((dx || dy)
	  && game_board_.isInBounds(adjacent)
	  && game_board_.getSymbol(adjacent) != game_board_.getDefaultSymbol()
	  && game_board_.getSymbol(adjacent) != sym
	  && isValidPath(adjacent, dx, dy, false, sym)) {return true;}
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
    
    current_player == 0 ? current_player = 1 : current_player = 0; 
  }
  results();
  
}
