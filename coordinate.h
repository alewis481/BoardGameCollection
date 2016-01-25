 /** 
   *
   */
#ifndef COORDINATE_H_
#define COORDINATE_H_

 /** 
   * Simple struct that stores row and column coordinates 
   */
struct Coordinate {
   /** 
   * Default constructor. 
   * Sets row and col to 0. 
   */
  Coordinate();
   /** 
   * A 2-arg constructor. 
   * Takes x and y coordinates and initializes row with x and col with y. 
   */
  Coordinate(int x, int y);  

   /** 
   * Row and column variables. Public by default. 
   */
  int row;    
  int col;
};

#endif // COORDINATE_H_
