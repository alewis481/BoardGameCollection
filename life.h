/** 
 *
 */

#ifndef LIFE_H_
#define LIFE_H_

#include "board_game.h"

/** 
 * Life is a derived class from BoardGame that implements Conway's Game of Life.
 * The member function play() uses ncurses library to increment generations 
 * gracefully on the terminal. 
 */
class Life : public BoardGame {
 public:
  /** 
   * Default no-arg constructor. Sets up a 50x50 board and sets cell_symbol to 
   * 'o'.
   */
  Life();
  
  
  /** 
   * Determines the next generation of the board using the standard rules for
   * the Game of Life and updates the board accordingly. 
   */
  void incrementTimeStep();

  /** 
   * Prints the board to the screen using the ncurses library. 
   */
  void ncPrintBoard();
  
  /** 
   * Randomly populates the board with living cells. Fills 50% of the board
   *   by default. 
   */
  void populateBoard();

  /** 
   * No players for Game of Life, so returns 0 by default. 
   */
  int numPlayers() const override;
  
  /** 
   * Inserts a living cell at the position specified. 
   * @param pos The position where a living cell is placed.
   * @param symbol Irrelevant here.
   */
  void doMove(Coordinate pos, char symbol) override;
  
  /** 
   * Returns true if board is empty and false otherwise. Will return false 
   *   indefinitely if there are only still lifes on the board.
   */
  bool isDone() const override;
  
  /** 
   * Returns true if position is unoccupied and position is in bounds. 
   * 
   * @param symbol Not used here. 
   */
  bool isLegalMove(Coordinate pos, char symbol='\0') const override;
  
  /** 
   * Currently does nothing..
   */
  void results() const override;
  
  /** 
   * Iterates through the generations and prints the board to the screen after
   * every iteration. 
   */
  void play() override;
 private:

  /** 
   * Counts the number of adjacent living cells. Returns the result. 
   * @param pos Checks each position adjacent to pos. 
   */
  int adjacentCells(Coordinate pos);
  
  /** 
   * Constructor that sets the board to a size specified by the parameter. 
   * @param board_dimension The dimension that the board is initialized to. 
   */
  Life(int board_dimension);

  
  char cell_symbol_;    //holds the symbol of the living cell
  
};

#endif // LIFE_H_
