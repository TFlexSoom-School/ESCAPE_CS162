/*
 * Tristan Hilbert
 * 3/12/18
 * Interprid Student Source File
 *
 */

#include "Interprid_Student.hpp"


Interprid_Student::Interprid_Student(int row, int col, UI* user): Maze_Person(row, col), _user_interface(user){}
Interprid_Student::~Interprid_Student(){}

char Interprid_Student::get_move(){
   return this->_user_interface->get_char();
}

char Interprid_Student::get_sym(){
   return '*';
}

/* Does nothing for there is no interaction between students */
void Interprid_Student::adjacent(int& score, bool same_space){}

bool Interprid_Student::random_spawn(){
   return false;
}
