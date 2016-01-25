/** 
 *
 */


#include <iostream>    //for std::cout
#include <algorithm>   //for std::adjacent_find
#include <functional>  //for std::not_equal_to

#include "tictactoe.h"
// TODO: replace magic number
TicTacToe::TicTacToe() : BoardGame(3), player_list_{Player('X'), Player('O')} {}


TicTacToe::TicTacToe(int board_size) : BoardGame(board_size),
				       player_list_{Player('X'), Player('O')} {}


//signal for failure? probably not. Does nothing if space not taken. 
void TicTacToe::doMove(Coordinate pos, char symbol) {
  if(game_board_.isInBounds(pos) && !game_board_.isOccupied(pos))
    game_board_.setSymbol(pos, symbol);
}

//if winner, winning_symbol_ set to winner's symbol, else set to default
char TicTacToe::findWinner() const {
  const int NUM_DIAGS = 2;
  
  //checks each row for 3-in-a-row winner
  for (int i = 0; i < game_board_.dimension(); ++i) {
    std::vector<char> row = game_board_.getRow(i);
    //checks if all elements the same and not equal to default symbol
    //adjacent find returns reference to 1st element not equal to front
    //or row.end() otherwise, all elements same if row.end() is returned
    if (row.front() != game_board_.getDefaultSymbol() &&
	std::adjacent_find(row.begin(), row.end(), std::not_equal_to<char>()) ==
	row.end())
      //row is filled with player symbol, so player symbol is winner
      return row.front();
  }
  
  
  for (int i = 0; i < game_board_.dimension(); ++i) {
    std::vector<char> col = game_board_.getCol(i);
    //checks if all elements the same and not equal to default symbol?
    if (col.front() != game_board_.getDefaultSymbol() &&
	adjacent_find(col.begin(), col.end(), std::not_equal_to<char>()) ==
	col.end())
      //col is filled with player symbol, so player symbol is winner
      return col.front();
  }
  
  for (int i = 0; i < NUM_DIAGS; ++i) {
   std::vector<char> diag = game_board_.getDiag(i);
    //checks if all elements the same and not equal to default symbol?
    if (diag.front() != game_board_.getDefaultSymbol() &&
	adjacent_find(diag.begin(), diag.end(), std::not_equal_to<char>()) ==
	diag.end())
      //col is filled with player symbol, so player symbol is winner
      return diag.front();
  }

  //return default if no winner
  return game_board_.getDefaultSymbol();
  
}

int TicTacToe::numPlayers() const {return player_list_.size();};



bool TicTacToe::isDone() const {
  return findWinner() != game_board_.getDefaultSymbol()
    || game_board_.isBoardFull();
}

bool TicTacToe::isLegalMove(Coordinate pos, char symbol) const {
  return game_board_.isInBounds(pos) && !game_board_.isOccupied(pos);
}


void TicTacToe::results() const {
  char winning_symbol = findWinner();
  //findWinner returns default symbol if there is no winner
  if(winning_symbol == game_board_.getDefaultSymbol()) 
    std::cout << "Game over. Game was a draw\n"; 
  else
    for(unsigned int i = 0; i < player_list_.size(); ++i) {
      if (player_list_[i].getSymbol() == winning_symbol)
	std::cout << "Game Over. Player " << i + 1 << " wins!\n";
    }


    
}


void TicTacToe::play() {
  //player array is 0 indexed, so player 1 is at index 0. 
  int current_player = 0;
  //resets the board. 
  reset();
  printBoard();
  while(!isDone()) {
    std::cout << "Player " << current_player + 1 << "'s turn. \n";
    //getCoordinateFromUser is a BoardGame function
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
