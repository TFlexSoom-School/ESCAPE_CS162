/*
 * Tristan Hilbert
 * 3/14/2018
 * Maze Header File
 *
 */

#ifndef __MAZE_HPP
#define __MAZE_HPP

#include "Maze_Level.hpp"

class Maze{

   private:
      std::vector<Maze_Level*> levels;
      int current_lev;
   public:
      Maze(const char ***, int, int, int);
      ~Maze();

      char ** get_current_lev();
      void level_up();
};

#endif
