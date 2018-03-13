/*
 * Tristan Hilbert
 * 3/8/18
 * Maze_Level Header
 *
 */

#ifndef __MAZE_LEVEL_HPP
#define __MAZE_LEVEL_HPP

#include "../Maze_Locations/Maze_Location.hpp"
#include <vector>
class Maze_Level{
   
   private:
      std::vector< std::vector<Maze_Location*> > map;

   public:
      Maze_Level(const char**, int, int);
      ~Maze_Level();

      void get_spawn(int&, int&);
      Maze_Location* at(int, int);
      void display_maze();
};

#endif