/*
 * Tristan Hilbert
 * 3/17/18
 * Game Source File
 *
 */

#include <iostream>
#include "Game.hpp"
/*
   std::vector<Maze_Object*> _game_objects;
   Maze& _maze;
   char ** _displayed;
   int score;
   */
void Game::try_loop(){}
void Game::game_loop(){}
void Game::update_display(){}
void Game::show_skill(){}
void Game::moves(){}
void Game::spawn(){}

Game::Game(Maze* maze): _game_objects(), _maze(maze), _displayed(NULL){
   this->update_display();
}

Game::Game(const Game& l): _game_objects(), _maze(new Maze(*l._maze)), _displayed(NULL){
   this->update_display();
}

Game::~Game(){
   for(int i = this->_maze->get_row() - 1; i >= 0; i --){
      delete [] this->_displayed[i];
   }
   delete [] this->_displayed;
}

void Game::get_display(){}
