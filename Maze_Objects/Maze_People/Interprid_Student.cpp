/*
 * Tristan Hilbert
 * 3/12/18
 * Interprid Student Source File
 *
 */

#include "Interprid_Student.hpp"


Interprid_Student::Interprid_Student(int row,int col): Maze_Person(row, col){}
Interprid_Student::~Interprid_Student(){}

char Interprid_Student::get_move(){
   return 'w'; //Ping UI for return value   
}

char Interprid_Student::get_sym(){
   return '*';
}

/* Does nothing for there is no interaction between students */
void Interprid_Student::adjacent(int& score, bool same_space){}

bool Interprid_Student::random_spawn(){
   return false;
}
