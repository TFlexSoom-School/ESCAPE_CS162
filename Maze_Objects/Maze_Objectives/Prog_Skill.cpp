/*
 * Tristan Hilbert
 * 3/12/18
 * Prog_Skill source file
 *
 */

#include "Prog_Skill.hpp"

Prog_Skill::Prog_Skill(int row, int col): Maze_Objective(row,col), _bearing(true){}

Prog_Skill::~Prog_Skill(){}

char Prog_Skill::get_sym(){
   if(this->_bearing){
      return '$';
   }
   return ' ';
}
void Prog_Skill::adjacent(int& score, bool same_space){
   if(same_space && _bearing){
      score ++;
      this->_bearing = false;
   }
}

void Prog_Skill::reset(){
   _bearing = true;
}

