/*
 * Tristan Hilbert
 * 3/19/2018
 * Victor_Exception Header
 *
 */

#ifndef __VICTORY_EXCEPTION_HPP
#define __VICTORY_EXCEPTION_HPP

#include <exception>

class Victory_Exception: public std::exception{

   public:
      Victory_Exception() noexcept;
      virtual ~Victory_Exception() noexcept;
      virtual const char* what() const noexcept;
};

#endif
