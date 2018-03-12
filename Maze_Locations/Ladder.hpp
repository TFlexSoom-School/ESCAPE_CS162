/*
 * Tristan Hilbert
 * 3/8/18
 * Ladder Header File
 *
 */

#ifndef __LADDER_HPP
#define __LADDER_HPP

#include "Open_Space.hpp"

class Ladder: public Open_Space{

   public:
      Ladder();
      ~Ladder();
      char get_sym();
};

#endif
