/*
 * Tristan Hilbert
 * 3/14/18
 * Maze Source File
 *
 */

#include "Maze.hpp"
#include <iostream>

Maze::Maze(const char *** maze_char_array, int floors, int rows, int cols):levels(), current_lev(0){
   for(int i = 0; i < floors; i ++){
      this->levels.push_back(new Maze_Level(maze_char_array[i], rows, cols));
   }
}
Maze::~Maze(){
   for(std::vector<Maze_Level*>::iterator it = this->levels.begin(); it != this->levels.end(); it ++){
      delete *it;
   }
}

char ** Maze::get_current_lev(){
   return this->levels.at(this->current_lev)->display_maze();
}

void Maze::level_up(){
   if(current_lev + 1 < this->levels.size())
      this->current_lev ++;
   else
      std::cerr << "Cannot level up past last level" << std::endl;
}
