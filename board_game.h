/** 
 *
 */

#ifndef BOARD_GAME_H_
#define BOARD_GAME_H_

#include <vector>
#include <string>

#include "player.h"
#include "board.h"
#include "coordinate.h"

/** 
 * BoardGame is the base class for the various board games implemented in this
 *   project. It implements a few functions that are useful for all the games, 
 *   and defines the interface that is expected for a board game derivative. 
 */
class BoardGame {
 public:
  /** 
   * BoardGame default 2-arg constructor. 
   *   Sets up the game board. Makes a board with dimension specified by 
   *   board_dimension, and sets every entry in the board to have the default
   *   symbol, which is '-' by default. 
   *   @param board_dimension The row and col dimension of the board. 
   *   @param default_grid_symbol The char each entry in the board is 
   *     initialized to. 
   */
  BoardGame(int board_dimension, char default_grid_symbol = '-');
  
  /** 
   * BoardGame destructor. 
   *   The base destructor does nothing outside the default. 
   */
  virtual ~BoardGame() {};

  /** 
   * Prints the board to the screen. Displays row and col coordinates as well, 
   *   in order to make specifying positions easier. 
   */
  void printBoard() const;

  /** 
   * Pure virtual function. Returns the number of players in the game. 
   */
  virtual int numPlayers() const = 0;
  
  /** 
   * Sets every entry in the board to the default symbol. 
   */
  virtual void reset();

  /** 
   *
   */
  virtual void doMove(Coordinate pos, char symbol) = 0;
  
  /** 
   * Pure virtual function. Returns true if game is finished. 
   */
  virtual bool isDone() const = 0;
  
  //not totally happy with the current optional symbol, change later?
  /** 
   * Pure virtual function. Returns true if the position specified is a
   *   a legal game move. 
   *   @param pos Specifies a position on the board. 
   *   @param symbol Specifies a player symbol. 
   */
  virtual bool isLegalMove(Coordinate pos, char symbol='\0') const = 0;
  
  /** 
   * Pure virtual function. Should print results of the game. 
   */
  virtual void results() const = 0;
  
  /** 
   * Pure virtual function. Executes the game logic. 
   */
  virtual void play() = 0;
  
  
 protected:
  /** 
   * Retrieves an x and y value from user and returns them together as a 
   *   coordinate object.
   */
  Coordinate getCoordinateFromUser();
  
  Board game_board_;  //holds the game board. 
  
  
  
 private:
  /** 
   * Private no-arg constructor. 
   *   Sets up an empty board. 
   */
  BoardGame();
  
};

#endif // BOARD_GAME_H_
