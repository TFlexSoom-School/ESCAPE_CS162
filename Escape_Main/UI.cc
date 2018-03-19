/*
 * Tristan Hilbert
 * 3/18/18
 * User Interface Source
 *
 */

#include "UI.hpp"

UI::UI(int row, int col): _wnd(newwin(row + 1, col, 0,0)), _row(row), _col(col), _score(0){
   this->_text = new char*[row];
   for(int i = 0; i < row; i ++){
      this->_text[i] = new char[col];
   }
   initscr();
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
   mvwprintw(this->_wnd, this->_row, this->_col * 3 / 4, "Score %d", this->_score);
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
      switch(c){
	 case KEY_UP:
	 case 'w':
	    return 'w';
	 case KEY_RIGHT:
	 case 'd':
	    return 'd';
	 case KEY_DOWN:
	 case 's':
	    return 's';
	 case KEY_LEFT:
	 case 'a':
	    return 'a';
	 case 'u':
	    return 'u';
	 case 'p':
	    return 'p';
	 default:
	    mvwprintw(this->_wnd, this->_row, 0, "%d", c);
	    this->update();
	    break;
      }
   }while(true); 
}
