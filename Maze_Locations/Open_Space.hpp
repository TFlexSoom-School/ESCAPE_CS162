/*
 * Tristan Hilbert
 * 3/8/18
 * Open Space Header File
 *
 */

#ifndef __OPEN_SPACE_HPP
#define __OPEN_SPACE_HPP

#include "Maze_Location.hpp"

class Open_Space: public Maze_Location{
   private:
      bool _contains_person;

   public:
      Open_Space();
      virtual ~Open_Space();
      bool is_occupiable();
      virtual char get_sym();
      virtual void contains_person_switch();
};

#endif
