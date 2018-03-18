/*
 * Tristan Hilbert
 * 3/17/18
 * Instructor Spawn Header File
 *
 */


#ifndef __INSTRUCTOR_SPAWN_HPP
#define __INSTRUCTOR_SPAWN_HPP

#include "Open_Space.hpp"

class Instructor_Spawn: public Open_Space{

   public:
      Instructor_Spawn();
      ~Instructor_Spawn();
      char get_sym();

};

#endif
