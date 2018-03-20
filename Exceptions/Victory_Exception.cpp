/*
 * Tristan Hilbert
 * 3/19/18
 * Victory_Exception Source File
 *
 */

#include "Victory_Exception.hpp"

Victory_Exception::Victory_Exception() noexcept: std::exception() {}
Victory_Exception::~Victory_Exception() noexcept{}
const char* Victory_Exception::what() const noexcept{
   return "Congratulations, Victory!";
}
