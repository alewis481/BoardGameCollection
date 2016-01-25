/** 
 * 
 */

#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#include "board_game.h"

/** 
 * TicTacToe is derived from BoardGame and provides the functions necessary 
 * to implement a game of tic-tac-toe. The member function play will 
 * set up a game automatically. 
 */
class TicTacToe : public BoardGame {
 public:
  /** 
   *Default no-arg constructor. 
   * Makes a 3x3 board, sets player 1 to 'X' and player 2 to 'O'.
   */
  TicTacToe();
  
  /** 
   * Returns the number of players. By default, it returns 2. 
   */
  int numPlayers() const override;
  
  /** 
   * Sets the char at pos to the symbol argument. Does nothing if space is
   * occupied or position is invalid. 
   * @param pos A coordinate on the board. 
   * @param symbol The player symbol to have the position set to.
   */
  void doMove(Coordinate pos, char symbol) override;
  
  /** 
   * Returns true if a player has 3-in-a-row, or if board is full. 
   */
  bool isDone() const override;
  
  /** 
   * Returns true if position is unoccupied. Symbol argument unneeded here. 
   */
  bool isLegalMove(Coordinate pos, char symbol = '\0') const override;
  
  /** 
   * If there is a winner, the player who wins is sent to stdout. Else announces
   *   that the game was a draw. 
   */
  void results() const override;
  
  /** 
   * Implements a functioning tic-tac-toe game. Gets coordinates for each player
   * from stdin, and plays the specified move if possible. Continues until the 
   * game is finished. 
   */
  void play();
  
 private:
  /** 
   * Private constructor. 
   * Allows custom board size. 
   */
  TicTacToe(int board_size);
  
  /** 
   * Determines which player is the winner. Returns default symbol if no winner.
   * User can determine winner using isDone() and results(). 
   */
  char findWinner() const;
  
  std::vector<Player> player_list_;    //holds the list of players in game

  
};

#endif // TICTACTOE_H_
