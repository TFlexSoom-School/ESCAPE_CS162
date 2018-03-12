/*
 * Tristan Hilbert
 * 3/8/18
 * Open_Space Source File
 *
 */

#include "Open_Space.hpp"

Open_Space::Open_Space():_contains_person(false){}

Open_Space::~Open_Space(){}

bool Open_Space::is_occupiable(){
   return !this->_contains_person;
}

char Open_Space::get_sym(){
   return ' ';
}

void Open_Space::contains_person_switch(){
   this->_contains_person = !this->_contains_person;
}
