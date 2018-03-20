/*
 * Tristan Hilbert
 * 3/18/18
 * User Interface Source
 *
 */

#define KEY_W 119
#define KEY_D 100
#define KEY_S 115
#define KEY_A 97
#define KEY_U 117 
#define KEY_P 112
#include <iostream>
#include "UI.hpp"

UI::UI(int row, int col): _row(row), _col(col), _score(0){
   this->_text = new char*[row];
   for(int i = 0; i < row; i ++){
      this->_text[i] = new char[col];
   }
   initscr();
   this->_wnd = newwin(row + 2, col, 0, 0);
   noecho();
   //raw();
   keypad(stdscr, FALSE);
   keypad(this->_wnd, TRUE);
   wrefresh(this->_wnd);
}

UI::~UI(){
   for(int i = this->_row - 1; i >= 0; i --){
      delete [] this->_text[i];
   }
   delete [] this->_text;
   delwin(this->_wnd);
   endwin();
}

void UI::update(){
   for(int i = 0; i < this->_row; i ++){
      wmove(this->_wnd, i, 0);
      for(int j = 0; j < this->_col; j ++){
	 waddch(this->_wnd, this->_text[i][j]);
      }
   }
   mvwprintw(this->_wnd, this->_row, 0, "Score %d", this->_score);
   wrefresh(this->_wnd);   
}
void UI::set_text(char ** array){
   for(int i = 0; i < this->_row; i ++){
      for(int j = 0; j < this->_col; j ++){
	 this->_text[i][j] = array[i][j]; 
      }
   }
   this->update();
}

void UI::set_score(int score){
   this->_score = score;
   this->update();
}

char UI::get_char(){
   int c;
   do{
      c = wgetch(this->_wnd);
      mvwprintw(this->_wnd, this->_row + 1, 0, "%d", c);
      this->update();
      switch(c){
	 case KEY_UP:
	 case KEY_W:
	    return 'w';
	 case KEY_RIGHT:
	 case KEY_D:
	    return 'd';
	 case KEY_DOWN:
	 case KEY_S:
	    return 's';
	 case KEY_LEFT:
	 case KEY_A:
	    return 'a';
	 case KEY_U:
	    return 'u';
	 case KEY_P:
	    return 'p';
	 default:
	    break;
      }
   }while(true);
}

void UI::victory(const char* msg){
   mvwprintw(this->_wnd, this->_row, 0, msg);
}

void UI::defeat(const char* msg){
   mvwprintw(this->_wnd, this->_row, 0, msg);
}
