/** 
 *
 */

#ifndef REVERSI_H_
#define REVERSI_H_

#include "board_game.h"

/**  
 * Reversi is derived from BoardGame and provides the functions necessary 
 * to implement a game of reversi. The member function play will 
 * set up a game automatically. 
 */

class Reversi : public BoardGame { 
 public:
  /** 
   * Default no-arg constructor
   *
   * Sets up an 8x8 board, 2 players with symbols 'X' and 'O', and places
   * 2 of each symbol in the center of the board
   */
  Reversi();
  
  
  /** 
   * Calls flip in each direction after a successful move by the player with 
   *   the symbol passed in the symbol parameter. 
   * 
   * @param pos     Specifies a position on the board
   * @param symbol  The symbol representing a player who just made a move
   */
  void flipAdjacent(Coordinate pos, char symbol);
  

  /** 
   * Returns the number of players in the game. Returns 2 by default. 
   */
  int numPlayers() const override;
  
  /** 
   * Sets each position on the board to the default symbol initially, then 
   *   puts two of each player's symbols in the center of the board, according
   *   to the usual rules for Reversi (or Othello really).
   */
  void reset() override;
  
  /** 
   * Determines whether setting character symbol at the position pos is legal, 
   *   and if so, sets the player symbol at that position. Follows by flipping
   *   any symbols to the symbol parameter if appropriate. If move is illegal, 
   *   nothing changes on the board. 
   * 
   * @param pos     Specifies a position on the board
   * @param symbol  Represents symbol of the player attempting to make a move
   */
  void doMove(Coordinate pos, char symbol) override;
  
  /** 
   * Determines whether the game is over by checking if either play is out of 
   *  available moves. Returns true if the game is over. 
   */
  bool isDone() const override;
  
  /** 
   * Returns true if player can legally make a move at pos. 
   *
   * @param pos     Specifies a position on the board
   * @param symbol  Represents symbol of the player attempting to make a move
   */
  bool isLegalMove(Coordinate pos, char symbol) const override;
  
  /** 
   * Prints the results of the game to stdout. If there was a winner, the 
   *   function will announce the winner. Otherwise, the game will announce a 
   *   draw. 
   */
  void results() const override;
  
  /** 
   * Implements a functioning tic-tac-toe game. Gets coordinates for each player
   *   from stdin, and plays the specified move if possible. Continues until the
   *   game is finished. 
   */
  void play();
  
 private:
  /** 
   * Private constructor. 
   * Allows custom board size
   */
  Reversi(int board_dimension);
  
  /** 
   * Recursive function that flips every symbol to the symbol parameter after 
   *   a valid move. dx and dy parameters specify the direction of the path. 
   *   valid parameter is used to determine if a set of pieces should have their
   *   symbols changed on the board. Returns true if same symbol is found on a 
   *   path. If same piece is found, flips each piece along the path. 
   *
   * @param pos    Specifies a position on the board
   * @param dx     Specifies a horizontal direction: should be either 0,1 or -1
   *                 for the game to work correctly
   * @param dy     Specifies a vertical direction: should be either 0,1 or -1
   *                 for the game to work correctly
   * @param valid  Flipped to true in recursive call if a piece on the board 
   *                 along the path specified by dx and dy is the same as the
   *                 symbol parameter
   * @param symbol The symbol representing the player
   */
  bool flip(Coordinate pos, int dx, int dy, bool valid, char symbol);

  /** 
   *  Determines whether a given path is legal.
   *   Returns true if the player's symbol at the position specified in the 
   *   parameter has an opposite player symbol in the direction specified by 
   *   dx and dy, as well as the player's symbol at the other end of a path 
   *   of opposite symbols
   * 
   * @param pos    Specifies a position on the board
   * @param dx     Specifies a horizontal direction: should be either 0,1 or -1
   *                 for the game to work correctly
   * @param dy     Specifies a vertical direction: should be either 0,1 or -1
   *                 for the game to work correctly
   * @param valid  Flipped to true in recursive call if a piece on the board 
   *                 along the path specified by dx and dy is the same as the
   *                 symbol parameter
   * @param symbol The symbol representing the player
   */
  bool isValidPath(Coordinate pos, int dx, int dy,bool valid,char symbol) const;
    
  std::vector<Player> player_list_;  //holds the list of players in game

};

#endif // REVERSI_H_
