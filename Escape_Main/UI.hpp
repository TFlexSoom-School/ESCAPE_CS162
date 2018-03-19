/*
 * Tristan Hilbert
 * 3/18/18
 * User Interface Header File
 *
 */

#ifndef __UI_HPP
#define __UI_HPP

#include <ncurses.h>
#include <cstdlib>

class UI{

   private:
      WINDOW * _wnd;
      int _score;
      char ** _text;
      int _row;
      int _col;

      void update();
   public:
      UI(int,int);
      ~UI();

      void set_text(char **);
      void set_score(int);
      char get_char();
};

#endif
