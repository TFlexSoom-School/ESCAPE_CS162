/*
 * Tristan Hilbert
 * 3/11/18
 * Maze_Person Source File
 *
 */

#include "Maze_Person.hpp"

Maze_Person::Maze_Person(int row, int col): Maze_Object(row, col){}
Maze_Person::~Maze_Person(){}
bool Maze_Person::can_occupy(){
   return true;
}
void Maze_Person::reset() {}
