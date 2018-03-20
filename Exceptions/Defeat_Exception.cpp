/*
 * Tristan Hilbert
 * 3/19/18
 * Defeat_Exception Source File
 *
 */

#include "Defeat_Exception.hpp"


Defeat_Exception::Defeat_Exception() noexcept : std::exception() {}
Defeat_Exception::~Defeat_Exception() noexcept {}
const char* Defeat_Exception::what() const noexcept {
   return "You Have Died! Prepare for restart!";
}
