/** 
 *
 */

#include "player.h"

Player::Player() : symbol_{'\0'} {}  

//TODO: error check this
Player::Player(char sym) : symbol_{sym} {}

char Player::getSymbol() const {return symbol_;}

//TODO: error-check this
void Player::setSymbol(char sym) {symbol_ = sym;}



