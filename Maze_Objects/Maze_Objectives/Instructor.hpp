/*
 * Tristan Hilbert
 * 3/12/18
 * Instructor Header File
 *
 */


#ifndef __INSTRUCTOR_HPP
#define __INSTRUCTOR_HPP

#include "Maze_Objective.hpp"

class Instructor: public Maze_Objective{

   public:

      Instructor(int, int);
      ~Instructor();
      char get_sym();
      void adjacent(int&, bool same_space = false);
};

#endif
