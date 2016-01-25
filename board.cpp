#include <algorithm>
#include <iostream>
#include "board.h"
#include <cstdio>

Board::Board() : board_dimension_{0}, board_(), default_symbol_{'-'} {}

Board::Board(int size,char sym) : board_dimension_{std::max(1,size)}, board_(board_dimension_, std::vector<char>(board_dimension_,sym)), default_symbol_{sym}
                        {
			 
			  resetBoard();
                        }
//does nothing right now
Board::~Board() {}

bool Board::isOccupied(Coordinate pos) const {
  if (isInBounds(pos))
    return board_[pos.row][pos.col] != default_symbol_;
  else
    //TODO: handle case when not in bounds
    return false;
  
  
}

bool Board::isInBounds(Coordinate pos) const {
  return pos.row >= 0 && pos.row < board_dimension_ && pos.col >= 0
    && pos.col < board_dimension_;
}

bool Board::isBoardFull() const {
  for (auto x : board_) {
    for (auto y : x)
      if (y == default_symbol_)
	return false;
  }
  return true;
}

char Board::getSymbol(Coordinate pos) const {
  if(isInBounds(pos))
    return board_[pos.row][pos.col];
  else
    //temporary, should define a good error symbol for this
    return '\0';
}

void Board::setSymbol(Coordinate pos, char symbol) {
  if (isInBounds(pos))
    board_[pos.row][pos.col] = symbol;
}

//returns nullptr on failure
std::vector<char> Board::getCol(int colIndex) const {
  if(colIndex < 0 || colIndex >= board_dimension_)
    //TODO: make sure this still works right after cast
    return std::vector<char>();
  
  std::vector<char> colVec(board_dimension_);
  for (int i = 0; i < board_dimension_; ++i) 
    colVec[i] = board_[i][colIndex];
  
  return colVec;
}

//returns nullptr on failure
std::vector<char> Board::getRow(int rowIndex) const {
  if (rowIndex < 0 || rowIndex >= board_dimension_)
    return std::vector<char>();
  return board_[rowIndex];
}

//2 main diagonals, indexed as 0 and 1
//returns nullptr on failure
std::vector<char> Board::getDiag(int diagIndex) const {
  if(diagIndex != 0 && diagIndex != 1)
    //    return dynamic_cast<std::vector<char>>(nullptr);
    return std::vector<char>();  //empty vector
  std::vector<char> diagVec(board_dimension_);
  for (int i = 0; i < board_dimension_; ++i) {
    if (diagIndex == 0)
      diagVec[i] = board_[i][i];
    else {
      diagVec[i] = board_[board_dimension_ - i - 1][i];
    }
  }
  return diagVec;
}

char Board::getDefaultSymbol() const {return default_symbol_;}

void Board::printBoard() const {
  //prints column coordinates to stdout
  std::cout << "  ";
  for (int i = 0; i < board_dimension_; ++i)
    std::cout <<  i << " ";
  
  std::cout << '\n';
  //prints the row coordinates and board contents to stdout
  for (int row = 0; row < board_dimension_; ++row) {
    std::cout << row << " "; 
    for (int col = 0; col < board_dimension_; ++col) {
      std::cout << board_[row][col] << " ";
    }
    std::cout << '\n';
  }
}

void Board::resetBoard() {
  //sets every entry in each row to default symbol
  for (auto x : board_)
    std::fill(x.begin(), x.end(), default_symbol_);
}

int Board::dimension() const {return board_dimension_;}


