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
      std::vector<Maze_Level*> _levels;
      int _current_lev;
   public:
      Maze(char ***, int, int, int);
      Maze(const Maze&);
      ~Maze();

      int get_row();
      int get_col();
      bool valid_space(int,int);

      char ** get_current_lev();
      void level_up();
};

#endif
