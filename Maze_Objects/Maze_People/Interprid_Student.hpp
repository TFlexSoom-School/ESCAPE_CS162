/*
 * Tristan Hilbert
 * 3/12/18
 * Interprid Student Header File
 *
 */

#ifndef __INTERPRID_STUDENT_HPP
#define __INTERPRID_STUDENT_HPP

#include "Maze_Person.hpp"

class Interprid_Student: public Maze_Person{

   private:
   //Private Pointer to HUD

   public:
      Interprid_Student(int,int);
      ~Interprid_Student();

      //Return true
      char get_move();
      
      //Derived from Maze_Object... Wait why don't u use multiple inh...
      //shhhhhhh not another word
      char get_sym();
      void adjacent(int& score);

};

#endif

