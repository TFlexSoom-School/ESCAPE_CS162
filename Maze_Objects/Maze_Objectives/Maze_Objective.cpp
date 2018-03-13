/*
 * Tristan Hilbert
 * 3/12/18
 * Maze_Objective Source
 *
 */

#include "Maze_Objective.hpp"


Maze_Objective::Maze_Objective(int row, int col): Maze_Object(row, col){}
Maze_Objective::~Maze_Objective(){}
bool Maze_Objective::can_occupy(){
   return false;
}
void Maze_Objective::reset(){}
