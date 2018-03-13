/*
 * Tristan Hilbert
 * 3/12/18
 * Maze_Objective Header File
 *
 */

#ifndef __MAZE_OBJECTIVE_HPP
#define __MAZE_OBJECTIVE_HPP

#include "../Maze_Object.hpp"

class Maze_Objective: public Maze_Object{

   public:

      Maze_Objective(int, int);
      virtual ~Maze_Objective();
      bool can_occupy();
      virtual void reset();
      virtual char get_sym() =0;
      virtual void adjacent(int&, bool same_space = false) =0;
};

#endif
