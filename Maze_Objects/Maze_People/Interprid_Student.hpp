/*
 * Tristan Hilbert
 * 3/12/18
 * Interprid Student Header File
 *
 */

#ifndef __INTERPRID_STUDENT_HPP
#define __INTERPRID_STUDENT_HPP

#include "Maze_Person.hpp"
#include "../../Escape_Main/UI.hpp"

class Interprid_Student: public Maze_Person{

   private:
      UI* _user_interface;

   public:
      Interprid_Student(int,int,UI*);
      ~Interprid_Student();

      char get_move();
      
      //Derived from Maze_Object... Wait why don't u use multiple inh...
      //shhhhhhh not another word
      char get_sym();
      bool random_spawn();
      void adjacent(int&, bool same_space = false);

};

#endif

