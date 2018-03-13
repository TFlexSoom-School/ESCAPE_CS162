/*
 * Tristan Hilbert
 * 3/11/18
 * TA source File
 *
 */

#include "TA.hpp"
#include <cstdlib>

TA::TA(int row, int col): Maze_Person(row, col), _shocked(TA_constants::unshocked){}
TA::~TA(){}
void TA::shock(){
   this->_shocked = TA_constants::shocked;
}

char TA::get_move(){
   if(this->_shocked > TA_constants::unshocked){
      this->_shocked --;
      return 0;
   }else{
      /* Four representing number of possible directions */
      switch(rand() % 4){ 
	 case 0:
	    return 'w';
	    break;
	 case 1:
	    return 'd';
	    break;
	 case 2:
	    return 's';
	    break;
	 case 3:
	    return 'a';
	    break;
        default:
	    return 'w';
      }   
   }
}

char TA::get_sym(){
   return 'T';
}

void TA::adjacent(int& score, bool same_space){
   score = 0;
   //The TA stole ur programming skills!!!
}
