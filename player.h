/** 
 *
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

/** 
 * The Player class used to hold the symbols of players in each board game. More
 * features may be added to this class in the future. 
 */
class Player {
 public: 
  /** 
   *No-arg constructor. Sets player symbol to '/0'.
   */
  Player(); 
  
  /** 
   * One-arg constructor. 
   * @param symbol Initializes the player symbol to the symbol argument. 
   */
  Player(char symbol);
  
  /** 
   * Default constructor. Nothing special necessary. 
   */
  ~Player() {};
  
  /** 
   * Returns the player symbol. 
   */
  char getSymbol() const;

  /** 
   * Sets the player symbol to the argument parameter. 
   */
  void setSymbol(char sym);
  
  
 private:
  char symbol_;    //holds the player symbol

  
};

#endif // BOARD_H_
