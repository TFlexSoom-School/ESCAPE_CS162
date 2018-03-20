/*
 * Tristan Hilbert
 * 3/12/18
 * Instructor Source File
 *
 */

#include "Instructor.hpp"
#include "../../Exceptions/Victory_Exception.hpp"
#include "../../Exceptions/Defeat_Exception.hpp"

Instructor::Instructor(int row, int col): Maze_Objective(row, col){}

Instructor::~Instructor(){}

char Instructor::get_sym(){
   return '%';
}

void Instructor::adjacent(int& score, bool same_space){
   if(score >= 3){
      throw Victory_Exception();
   }else{
      throw Defeat_Exception();
   }
}

bool Instructor::random_spawn(){
   return false;
}
