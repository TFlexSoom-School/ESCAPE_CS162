/*
 * Tristan Hilbert
 * 3/11/18
 * Maze_Object Source File
 *
 */

#include "Maze_Object.hpp"


Maze_Object::Maze_Object(int row, int col): _row(row), _col(col){}

Maze_Object::~Maze_Object(){}

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

bool Maze_Object::random_spawn(){
   return true;
}

void Maze_Object::adjacent_check(int row, int col, int& score){
   if(this->_row == row){
      if(this->_col - col == -1 || this->_col - col == 1){
	 this->adjacent(score, false);
      }else if(this->_col == col){
	 this->adjacent(score, true);
      }
   }else if(this->_col == col){
      if(this->_row - row == -1 || this->_row - row == 1){
	 this->adjacent(score, false);
      }
   }
}
