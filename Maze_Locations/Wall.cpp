/*
 * Tristan Hilbert
 * 3/8/18
 * Wall Source File
 *
 */

#include "Wall.hpp"

Wall::Wall(){}
Wall::~Wall(){}

bool Wall::is_occupiable(){
   return false;
}

char Wall::get_sym(){
   return '#';
}

void Wall::contains_person_switch(){}
