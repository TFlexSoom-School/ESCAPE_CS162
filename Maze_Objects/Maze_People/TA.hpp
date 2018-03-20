/*
 * Tristan Hilbert
 * 3/11/18
 * TA Header File
 *
 */

#ifndef __TA_HPP
#define __TA_HPP
#include "Maze_Person.hpp"

namespace TA_constants{
   const int shocked = 10;
   const int unshocked = 0;
}

class TA: public Maze_Person{

   private:
      //0 means able to move >0 means cannot move
      int _shocked;

   public:
      TA(int, int);
      ~TA();
      void shock();
      virtual void reset();
      virtual char get_move();
      
      //Derived from Maze_Object... Wait why don't u use multiple inh...
      //shhhhhhh not another word
      virtual char get_sym();
      virtual void adjacent(int&, bool same_space = false);
   

};

#endif
