/*
 * Tristan Hilbert
 * 3/11/18
 * Maze_Person Header file
 *
 */

#ifndef __MAZE_PERSON_HPP
#define __MAZE_PERSON_HPP
#include "Maze_Object.hpp"

class Maze_Person: public Maze_Object{

   public:
      Maze_Person(int, int);
      virtual ~Maze_Person();

      //Return true
      bool can_occupy();
      virtual char get_move() = 0;
      
      //Derived from Maze_Object... Wait why don't u use multiple inh...
      //shhhhhhh not another word
      virtual char get_sym() =0;
      virtual void adjacent(int& score) =0;

};

#endif
