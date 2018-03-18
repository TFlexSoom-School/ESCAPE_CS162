/*
 * Tristan Hilbert
 * 3/17/18
 * Game Source File
 *
 */

#include <iostream>
#include <cstdlib>
#include "Game.hpp"
#include "../Maze_Objects/Maze_Objectives/Maze_Objective.hpp"
#include "../Maze_Objects/Maze_Objectives/Prog_Skill.hpp"
#include "../Maze_Objects/Maze_Objectives/Instructor.hpp"

#include "../Maze_Objects/Maze_People/Maze_Person.hpp"
#include "../Maze_Objects/Maze_People/TA.hpp"
#include "../Maze_Objects/Maze_People/Interprid_Student.hpp"

/*
   std::vector<Maze_Object*> _game_objects;
   Maze& _maze;
   char ** _displayed;
   int score;
   */

void Game::create_objects(){
   this->_game_objects.push_back(new TA(-1,-1));
   this->_game_objects.push_back(new TA(-1,-1));
   this->_game_objects.push_back(new Prog_Skill(-1,-1));
   this->_game_objects.push_back(new Prog_Skill(-1,-1));
   this->_game_objects.push_back(new Prog_Skill(-1,-1));
   this->_game_objects.push_back(new Interprid_Student(-1,-1));
   this->_game_objects.push_back(new Instructor(-1,-1));
}

void Game::try_loop(){} /* TODO */

void Game::game_loop(){} /* TODO */

void Game::current_lev_display(){
   if(this->_displayed != NULL){
      for(int i = this->_maze->get_row() - 1; i >= 0; i --){
         delete [] this->_displayed[i];
      }
      delete [] this->_displayed;
   }

   this->_displayed = this->_maze->get_current_lev();
}

void Game::show_skill(){} /* TODO */
void Game::moves(){} /* TODO */
void Game::spawn(){
   int number_spawn = 0;
   do{
      for(int i = 0; i < this->_maze->get_row(); i ++){
	 for(int j = 0; j < this->_maze->get_col(); j ++){
	    switch(this->_displayed[i][j]){
	       case '@':
		  this->spawn_student(i,j);
		  break;
	       case '%':
		  this->spawn_instructor(i,j);
		  break;
	       case ' ':
		  this->random_spawn(i, j, number_spawn);
		  break;
	       default: /* Wall */
		  break;
	    }
	 }
      }

      /* Verify everything spawn */
      for(std::vector<Maze_Object *>::iterator it = this->_game_objects.begin(); 
	    it != this->_game_objects.end(); it ++){
	 if((*it)->get_row() == -1){
	    continue;
	 }
      }
      break;
   }while(true);
}

void Game::random_spawn(int i, int j, int& number_spawn){
   if(this->random_spawn_chance(i, j, number_spawn)){
      for(int i = 0; i < this->_game_objects.size(); i ++){
	 if(_game_objects.at(i)->random_spawn() && _game_objects.at(i)->get_row() == -1){
	    _game_objects.at(i)->set_location(i,j);
	    number_spawn ++;
	 }else if(!_game_objects.at(i)->random_spawn()){
	    number_spawn ++;
	 }
      }
   }
}

bool Game::random_spawn_chance(const int& row, const int& col,const int& number_spawn){
   int modulus = row * this->_maze->get_col();
   modulus = (this->_maze->get_row() * this->_maze->get_col()) - modulus;
   return (rand() % modulus <= this->_game_objects.size() - number_spawn * 2); /* Chance increases as spots left decreases */
}

void Game::spawn_student(int row, int col){
   Interprid_Student* pStudent;
   for(std::vector<Maze_Object *>::iterator it = this->_game_objects.begin(); 
	 it != this->_game_objects.end(); it ++){
      pStudent = dynamic_cast<Interprid_Student*>(*it);
      if(pStudent != NULL){
	 pStudent->set_location(row,col);
      }
   }
}

void Game::spawn_instructor(int row, int col){
   Instructor* pInstructor;
   for(std::vector<Maze_Object *>::iterator it = this->_game_objects.begin(); 
	 it != this->_game_objects.end(); it ++){
      pInstructor = dynamic_cast<Instructor*>(*it);
      if(pInstructor != NULL){
	 pInstructor->set_location(row,col);
      }
   }
}

void Game::level_up(){} /* TODO */

Game::Game(Maze* maze): _game_objects(), _maze(maze), _displayed(NULL), _score(0){ 
   this->create_objects();
   this->current_lev_display();
   this->spawn();
}

Game::Game(const Game& l): _game_objects(), _maze(new Maze(*l._maze)), _displayed(NULL), _score(0){
   this->create_objects();
   this->spawn();
}

Game::~Game(){
   if(this->_displayed != NULL){
      for(int i = this->_maze->get_row() - 1; i >= 0; i --){
	 delete [] this->_displayed[i];
      }
      delete [] this->_displayed;
   }
   delete this->_maze;
}

void Game::get_display(){} /* TODO */


