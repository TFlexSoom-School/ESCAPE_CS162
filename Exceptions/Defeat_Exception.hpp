/*
 * Tristan Hilbert
 * 3/19/18
 * Defeat_Exception Header File
 *
 */

#ifndef __DEFEAT_EXCEPTION_HPP
#define __DEFEAT_EXCEPTION_HPP

#include <exception>

class Defeat_Exception: public std::exception{

   public:
      Defeat_Exception() noexcept;
      virtual ~Defeat_Exception() noexcept;
      virtual const char* what() const noexcept;


};

#endif
