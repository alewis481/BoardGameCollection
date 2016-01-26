/** 
 *
 */

#include <algorithm> //for adjacent find
#include <cstdlib> //for rand
#include <ncurses.h> //for printing
#include <unistd.h> //for usleep
#include <cmath> // for pow

#include "life.h"

Life::Life() : BoardGame(50), cell_symbol_{'o'} {populateBoard();}

Life::Life(int board_dimension) : BoardGame(board_dimension),cell_symbol_{'o'}
{populateBoard();}
//void Life::reset() {

//}

void Life::populateBoard() {
  //fill 50% of the board at random by default. 
  double board_fill_percentage{.5 * pow(game_board_.dimension(), 2)};
  
  srand(time(NULL));

  //pick random x,y coordinates and insert a living cell at that position
  for (int population = 0; population < board_fill_percentage; ++population) {
      int x = rand() % game_board_.dimension();
      int y = rand() % game_board_.dimension();
      doMove(Coordinate(x,y), cell_symbol_);
    }
  
}

int Life::adjacentCells(Coordinate pos) {
  //holds the number of living cells adjacent to pos 
  int num_adjacent_cells = 0;
  //sets up coordinate variables to each entry in the board adjacent to pos
  Coordinate top_left(pos.row - 1, pos.col - 1);
  Coordinate top(pos.row - 1, pos.col);
  Coordinate top_right(pos.row - 1, pos.col + 1);
  Coordinate right(pos.row, pos.col + 1);
  Coordinate bottom_right(pos.row + 1, pos.col + 1);
  Coordinate bottom(pos.row + 1, pos.col);
  Coordinate bottom_left(pos.row + 1, pos.col - 1);
  Coordinate left(pos.row, pos.col - 1);


  std::vector<Coordinate> adjacent_positions ={top_left, top, top_right,
					       left,          right,
					       bottom_left,bottom,bottom_right};
  // checks if the adjacent coordinate is in bounds and whether it is
  //a living cell. If so, increment num_adjacent_cells variable
  for (Coordinate position : adjacent_positions) {
    if(game_board_.isInBounds(position) &&
       game_board_.getSymbol(position) == cell_symbol_) {++num_adjacent_cells;}
  }
  return num_adjacent_cells;
}

void Life::incrementTimeStep() {
  using charVector = std::vector<char>;
  //consts used to determine whether cell is alive in next generation
  const int UNDERPOPULATED = 2;
  const int OVERPOPULATED = 3;
  const int REPRODUCED = 3;
  
  //go through each cell? Current implementation makes a new game board.
  std::vector<charVector> newBoard(game_board_.dimension(),
				   charVector(game_board_.dimension(),
					      game_board_.getDefaultSymbol()));

  //this nested for loop goes through each entry in the board and determines
  //whether the next generation has a living cell in each entry or not
  for (int row = 0; row < game_board_.dimension(); ++row) {
    for (int col = 0; col < game_board_.dimension(); ++col) {
      //number of living adjacent cells
      int num_adjacent_cells = adjacentCells(Coordinate(row, col));
      //the if-else if-else statements implement the Game of Life rules for
      //determining the next generation board
      if(game_board_.getSymbol(Coordinate(row,col)) ==
	 game_board_.getDefaultSymbol() &&
	 num_adjacent_cells == REPRODUCED) {
	newBoard[row][col] = cell_symbol_;
      }
      else if(game_board_.getSymbol(Coordinate(row,col)) ==
	      game_board_.getDefaultSymbol()) {
	newBoard[row][col] = game_board_.getDefaultSymbol();
      }
      else if(num_adjacent_cells < UNDERPOPULATED ||
	      num_adjacent_cells > OVERPOPULATED) {
	newBoard[row][col] = game_board_.getDefaultSymbol();
      }
      else {
	newBoard[row][col] = cell_symbol_;
      }
    }
  }
  //copy the new board to the class's board
  for(int row = 0; row < game_board_.dimension(); ++row) {
    for (int col = 0; col < game_board_.dimension(); ++col) {
      game_board_.setSymbol(Coordinate(row, col), newBoard[row][col]);
    }
  }
  

}

int Life::numPlayers() const { return 0; }

//symbol not used here
void Life::doMove(Coordinate pos, char symbol) {
  if(isLegalMove(pos))
    game_board_.setSymbol(pos, cell_symbol_);
}

bool Life::isDone() const {
  //game over when board is empty i guess
  for(int rowIndex = 0; rowIndex < game_board_.dimension(); ++rowIndex) {
    std::vector<char> row = game_board_.getRow(rowIndex);
    //adjacent find returns reference to 1st element not equal to front
    //or row.end() otherwise, all elements same if row.end() is returned
    if (row.front() == game_board_.getDefaultSymbol() &&
	std::adjacent_find(row.begin(), row.end(), std::not_equal_to<char>()) ==
	row.end())
      continue;     //continue checking rows if entire row is default symbol
    else
      return false;
  }
  return true;
}

bool Life::isLegalMove(Coordinate pos, char symbol) const {
  if(game_board_.isInBounds(pos) && !game_board_.isOccupied(pos))
    return true;
  return false;
}

void Life::results() const {
  //anything special here? 
}


void Life::ncPrintBoard() {
  for(int row = 0; row < game_board_.dimension(); ++row) {
    for (int col = 0; col < game_board_.dimension(); ++col) {
      //uses ncurses method to write character to the screen
      mvaddch(col, row, game_board_.getSymbol(Coordinate(row, col)));
    }
  }
  
}


void Life::play() {
  //initialize screen
  initscr();
  noecho();
  //no cursor
  curs_set(false);


  while(!isDone()) {
    incrementTimeStep();
    ncPrintBoard();
    refresh();
    //sleep long enough that the evolutions can be watched
    usleep(100000);
  }
  //close ncurses window
  endwin();
  
}
