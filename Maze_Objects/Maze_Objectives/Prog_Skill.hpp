/*
 * Tristan Hilbert
 * 3/12/18
 * Programming Skill Header
 *
 *
 */

#ifndef __PROG_SKILL_HPP
#define __PROG_SKILL_HPP

#include "Maze_Objective.hpp"

class Prog_Skill: public Maze_Objective{

   private:
      bool _bearing;

   public:
      Prog_Skill(int, int);
      ~Prog_Skill();
      void reset();
      char get_sym();
      void adjacent(int&, bool same_space = false);
};

#endif
