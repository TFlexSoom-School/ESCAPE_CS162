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
   Maze* _maze;
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

void Game::try_loop(){
   do{
      try{
	 this->game_loop();
      }catch(...){
	 std::cerr << "Unknown Exception Caught" << std::endl;
	 break;
      }

   }while(true);
}

void Game::game_loop(){
   do{
      //Print Maze to UI TODO
      this->moves();
      this->get_display();
   }while(true);
}

void Game::current_lev_display(){
   if(this->_displayed != NULL){
      for(int i = this->_maze->get_row() - 1; i >= 0; i --){
	 delete [] this->_displayed[i];
      }
      delete [] this->_displayed;
   }

   this->_displayed = this->_maze->get_current_lev();
}

bool Game::show_skill(){
   if(this->_score > 0){
      TA* pta;
      for(std::vector<Maze_Object*>::iterator it = this->_game_objects.begin();
	    it != this->_game_objects.end(); it ++){
	 pta = dynamic_cast<TA*>(*it);
	 if(pta != NULL){
	    pta->shock();
	 }
      }
      return true;
   }
   return false;
}

void Game::moves(){
   Interprid_Student * pStudent;
   for(std::vector<Maze_Object*>::iterator it = this->_game_objects.begin(); 
	 it != this->_game_objects.end(); it++){
      pStudent = dynamic_cast<Interprid_Student *>(*it);
      if(pStudent != NULL){
         this->check_adjacency(pStudent);
         this->get_command(*it);
         this->check_adjacency(pStudent);	 
      }else
         this->get_command(*it);

   }
}

void Game::check_adjacency(Interprid_Student * pStudent){
   for(std::vector<Maze_Object*>::iterator it = this->_game_objects.begin(); 
	 it != this->_game_objects.end(); it++){
      (*it)->adjacent_check(pStudent->get_row(), pStudent->get_col(), this->_score);
   }
}

void Game::get_command(Maze_Object * it){
   Maze_Person* pPerson;
   char command;
   pPerson = dynamic_cast<Maze_Person*>(it);
   if(pPerson != NULL){
      do{
	 command = pPerson->get_move();
	 switch(command){
	    case 'w':
	    case 'd':
	    case 's':
	    case 'a':
	       if(get_move(pPerson, command)){
		  return;
	       }
	       break;
	    case 'p':
	       if(this->show_skill())
		  return;
	       break;
	    case 'u':
	       this->level_up(pPerson);
	       break;
	    default:
	       return;
	 }
      }while(true);
   }

}

bool Game::get_move(Maze_Person * pPerson, char command){
   switch(command){
      case 'w':
	 if(this->valid_space(pPerson->get_row() - 1, pPerson->get_col())){
	    pPerson->set_location(pPerson->get_row() - 1, pPerson->get_col());
	    return true;
	 }
	 break;
      case 'd':
	 if(this->valid_space(pPerson->get_row(), pPerson->get_col() + 1)){
	    pPerson->set_location(pPerson->get_row(), pPerson->get_col() + 1);
	    return true;
	 }
	 break;
      case 's':
	 if(this->valid_space(pPerson->get_row() + 1, pPerson->get_col())){
	    pPerson->set_location(pPerson->get_row() + 1, pPerson->get_col());
	    return true;
	 }
	 break;
      case 'a':
	 if(this->valid_space(pPerson->get_row(), pPerson->get_col()) - 1){
	    pPerson->set_location(pPerson->get_row(), pPerson->get_col() - 1);
	    return true;
	 }
   }
   return false;
}

bool Game::valid_space(int row, int col){
   if(!this->_maze->valid_space(row, col)){
      return false;
   }
   for(std::vector<Maze_Object *>::iterator it = this->_game_objects.begin(); 
	 it != this->_game_objects.end(); it ++){
      if((*it)->get_row() == row && (*it)->get_col() == col && (*it)->can_occupy()){
	 return false;
      } 
   }
   return true;
}

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
	 if((*it)->get_row() == -1 && (*it)->random_spawn()){
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

void Game::level_up(Maze_Person * pPerson){
   if(this->_displayed[pPerson->get_row()][pPerson->get_col()] == '^'){
      this->_maze->level_up();
      this->current_lev_display();
      for(std::vector<Maze_Object *>::iterator it = this->_game_objects.begin();
	    it != this->_game_objects.end(); it ++){
         (*it)->set_location(-1,-1);
      }
      this->spawn();
   }
} 

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


