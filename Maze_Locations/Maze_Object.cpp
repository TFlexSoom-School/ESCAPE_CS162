/*
 * Tristan Hilbert
 * 3/11/18
 * Maze_Object Source File
 *
 */

#include "Maze_Object.hpp"


Maze_Object::Maze_Object(int row, int col): _row(row), _col(col){}

void Maze_Object::set_location(int row, int col){
   this->_row = row;
   this->_col = col;
}

int Maze_Object::get_row(){
   return this->_row;
}

int Maze_Object::get_col(){
   return this->_col;
}
