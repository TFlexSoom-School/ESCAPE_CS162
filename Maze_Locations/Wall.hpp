/*
 * Tristan Hilbert
 * 3/8/18
 * Wall Header File
 */


#ifndef __WALL_HPP
#define __WALL_HPP

#include "Maze_Location.hpp"

class Wall: public Maze_Location{
   
   public:
      Wall();
      ~Wall();
      bool is_occupiable();
      virtual char get_sym();
};

#endif
