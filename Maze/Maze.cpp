/*
 * Tristan Hilbert
 * 3/14/18
 * Maze Source File
 *
 */

#include "Maze.hpp"
#include <iostream>

Maze::Maze(char *** maze_char_array, int floors, int rows, int cols):_levels(), _current_lev(0){
   for(int i = 0; i < floors; i ++){
      this->_levels.push_back(new Maze_Level(maze_char_array[i], rows, cols));
   }
}

Maze::Maze(const Maze& l): _levels(), _current_lev(0){
   for(int i = 0; i < l._levels.size(); i ++){
      this->_levels.push_back(new Maze_Level(*l._levels.at(i)));
   }
}

Maze::~Maze(){
   for(std::vector<Maze_Level*>::iterator it = this->_levels.begin(); it != this->_levels.end(); it ++){
      delete *it;
   }
}

char ** Maze::get_current_lev(){
   return this->_levels.at(this->_current_lev)->display_maze();
}

void Maze::level_up(){
   if(this->_current_lev + 1 < this->_levels.size())
      this->_current_lev ++;
   else
      std::cerr << "Cannot level up past last level" << std::endl;
}

int Maze::get_row(){
   this->_levels.at(this->_current_lev)->get_row();
}
int Maze::get_col(){
   this->_levels.at(this->_current_lev)->get_col();
}

bool Maze::valid_space(int row, int col){
   return this->_levels.at(this->_current_lev)->at(row,col)->is_occupiable();
}

Maze_Location* Maze::at(int row, int col){
   return this->_levels.at(this->_current_lev)->at(row,col);
}
