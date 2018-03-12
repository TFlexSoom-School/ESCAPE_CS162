/*
 * Tristan Hilbert
 * 3/8/18
 * Student Spawn Header File
 *
 */

#ifndef __STUDENT_SPAWN_HPP
#define __STUDENT_SPAWN_HPP

#include "Open_Space.hpp"

class Student_Spawn: public Open_Space{

   public:
      Student_Spawn();
      ~Student_Spawn();
      virtual char get_sym();

};

#endif
