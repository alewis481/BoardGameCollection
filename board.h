/** 
 *
 */

//current assumptions.. pos is char and board is of chars

#ifndef BOARD_H_
#define BOARD_H_

#include <vector>

#include "coordinate.h"

/** 
 *  Board is a container class that implements the board that is used by the
 *  base BoardGame class as well as the derived class from BoardGame.  
 */
class Board {
 public:
  
  /** 
  *  Public constructor for Board. 
  *  @param size Board is set to have dimensions set by size, set to 1 if input
  *    is < 1
  *  @param sym This is the symbol that each board entry is initialized with
  */
  Board(int size, char sym = '-');
  
  /** 
  *  A destructor.
  *  Default destructor. Vector deallocates memory automatically, so nothing 
  *    special is needed. 
  */
  ~Board();
  
  /** 
  *  Determines whether position on the board is occupied by some player's 
  *    symbol 
  *  @param pos A coordinate position on the board. Returns true if char at the 
  *    position specified is something other than the default symbol. 
  *    Will return false if coordinate is invalid.
  */
  bool isOccupied(Coordinate pos) const;
  
  /** 
  *  Returns true if coordinate is within boundaries of the board. 
  *  @param pos A coordinate position on the board. 
  */
  bool isInBounds(Coordinate pos) const;
  
  /** 
  * Returns true if the board is filled with chars different from the default 
  *   symbol.
  */
  bool isBoardFull() const;
  
  /** 
  *  Returns the character stored at the specified position on the board. If 
  *    the position is invalid, the character '\0' is returned. 
  *  @param pos A coordinate position on the board. 
  */
  char getSymbol(Coordinate pos) const;
  
  /** 
  *  Sets the board entry at the specified coordinate to symbol. 
  *  @param pos A coordinate position on the board
  *  @param symbol A character to be placed in the specified position
  */
  void setSymbol(Coordinate pos, char symbol);
  
  /** 
  *  Returns a copy of a row on the board specified by the row index. If row 
  *    index is invalid, an empty vector is returned. 
  *  @param rowIndex A number between 0 and board_dimension_ - 1
  */
  std::vector<char> getRow(int rowIndex) const;
  
  /** 
  *  Returns a copy of a column on the board specified by the col index. If col
  *    index is invalid, an empty vector is returned. 
  *  @param colIndex A number between 0 and board_dimension_ - 1
  */
  std::vector<char> getCol(int colIndex) const;
  
  /** 
  *  Returns a copy of a main diagonal on the board specified by the diag index.
  *    If diag index is invalid, an empty vector is returned. 
  *  @param diagIndex 0 is main anti-diagonal, 1 is main diagonal
  */
  std::vector<char> getDiag(int diagIndex) const;
  
  /** 
  *  Returns the default board symbol
  */
  char getDefaultSymbol() const;
  
  /** 
  *  Prints the board to the screen 
  */
  void printBoard() const;
  
  /** 
  *  Sets each entry in the board to the default symbol. 
  */
  void resetBoard();
  
  /** 
  *  Returns the dimension of the board. i.e. if board is nxn, returns n. 
  */
  int dimension() const;
  
 private:
  /** 
  * No-arg contructor. Sets board dimension to 0, uses default constructor for
  * the 2d board vector, and sets the default symbol to '-'.
  */
  Board();
  
  int board_dimension_;
  std::vector<std::vector<char>> board_;
  const char default_symbol_;

};

#endif // BOARD_H_
