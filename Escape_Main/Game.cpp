/*
 * Tristan Hilbert
 * 3/17/18
 * Game Source File
 *
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <thread>
#include <chrono>
#include "Game.hpp"

#include "../Maze_Objects/Maze_Objectives/Maze_Objective.hpp"
#include "../Maze_Objects/Maze_Objectives/Prog_Skill.hpp"
#include "../Maze_Objects/Maze_Objectives/Instructor.hpp"
#include "../Maze_Objects/Maze_People/TA.hpp"
#include "../Exceptions/Victory_Exception.hpp"
#include "../Exceptions/Defeat_Exception.hpp"

void Game::create_objects(){
   /* Establishes Z-Order */
   this->_game_objects.push_back(new Prog_Skill(-1,-1));
   this->_game_objects.push_back(new Prog_Skill(-1,-1));
   this->_game_objects.push_back(new Prog_Skill(-1,-1));
   this->_game_objects.push_back(new Interprid_Student(-1,-1, this->_user_interface));
   this->_game_objects.push_back(new TA(-1,-1));
   this->_game_objects.push_back(new TA(-1,-1));
   this->_game_objects.push_back(new Instructor(-1,-1));
}

void Game::try_loop(){
   do{
      try{
	 this->game_loop();
      }catch(Victory_Exception & e){
	 this->_user_interface->victory(e.what());	   
	 std::this_thread::sleep_for (std::chrono::seconds(2));
	 break;
      }catch(Defeat_Exception & e){
	 this->_user_interface->defeat(e.what());
	 std::this_thread::sleep_for (std::chrono::seconds(2));
	 this->restart(); 
      }catch(std::exception & e){
	 std::cerr << e.what() << std::endl;
	 break;
      }catch(...){
	 std::cerr << "Unknown Exception Caught" << std::endl;
	 break;
      }

   }while(true);
}

void Game::game_loop(){
   do{
      this->get_display();
      this->moves();
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
      this->_score --;
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
	    case 0:
	       return;
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
	    this->set_location(pPerson->get_row() - 1, pPerson->get_col(), pPerson);
	    return true;
	 }
	 break;
      case 'd':
	 if(this->valid_space(pPerson->get_row(), pPerson->get_col() + 1)){
	    this->set_location(pPerson->get_row(), pPerson->get_col() + 1, pPerson);
	    return true;
	 }
	 break;
      case 's':
	 if(this->valid_space(pPerson->get_row() + 1, pPerson->get_col())){
	    this->set_location(pPerson->get_row() + 1, pPerson->get_col(), pPerson);
	    return true;
	 }
	 break;
      case 'a':
	 if(this->valid_space(pPerson->get_row(), pPerson->get_col() - 1)){
	    this->set_location(pPerson->get_row(), pPerson->get_col() - 1, pPerson);
	    return true;
	 }
	 break;
   }
   return false;
}

bool Game::valid_space(int row, int col){
   if(this->_maze->valid_space(row, col)){
      return true;
   }
   return false;
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

void Game::random_spawn(int row, int col, int& number_spawn){
   if(this->random_spawn_chance(row, col, number_spawn)){
      for(int i = 0; i < this->_game_objects.size(); i ++){
	 if(_game_objects.at(i)->random_spawn() && _game_objects.at(i)->get_row() == -1){
	    this->set_location(row,col,i);
	    number_spawn ++;
	    break;
	 }else if(!_game_objects.at(i)->random_spawn()){
	    number_spawn ++;
	 }
      }
   }
}

bool Game::random_spawn_chance(const int& row, const int& col,const int& number_spawn){
   int modulus = row * this->_maze->get_col();
   modulus = (this->_maze->get_row() * this->_maze->get_col()) - modulus;
   return (rand() % modulus <= this->_game_objects.size() - number_spawn); /* Chance increases as spots left decreases */
}

void Game::spawn_student(int row, int col){
   Interprid_Student* pStudent;
   for(std::vector<Maze_Object *>::iterator it = this->_game_objects.begin(); 
	 it != this->_game_objects.end(); it ++){
      pStudent = dynamic_cast<Interprid_Student*>(*it);
      if(pStudent != NULL){
	 this->set_location(row, col, pStudent);
      }
   }
}

void Game::spawn_instructor(int row, int col){
   Instructor* pInstructor;
   for(std::vector<Maze_Object *>::iterator it = this->_game_objects.begin(); 
	 it != this->_game_objects.end(); it ++){
      pInstructor = dynamic_cast<Instructor*>(*it);
      if(pInstructor != NULL){
	 this->set_location(row, col, pInstructor);
      }
   }
}

void Game::level_up(Maze_Person * pPerson){
   if(this->_displayed[pPerson->get_row()][pPerson->get_col()] == '^'){
      for(std::vector<Maze_Object *>::iterator it = this->_game_objects.begin();
	    it != this->_game_objects.end(); it ++){
	 this->set_location(-1, -1, *it);
	 (*it)->reset();
      }
      this->_maze->level_up();
      this->current_lev_display();
      this->spawn();
      this->get_display();
   }
} 

Game::Game(Maze* maze, UI* user): 
   _game_objects(), 
   _maze(maze), 
   _displayed(NULL), 
   _score(0),
   _user_interface(user)
{
   srand(time(NULL)); 
   this->create_objects();
   this->current_lev_display();
   this->spawn();
   this->try_loop();
}

Game::Game(const Game& l): 
   _game_objects(), 
   _maze(new Maze(*l._maze)), 
   _displayed(NULL), 
   _score(0),
   _user_interface(l._user_interface)
{
   srand(time(NULL));
   this->create_objects();
   this->spawn();
   this->try_loop();
}

Game::~Game(){
   if(this->_displayed != NULL){
      for(int i = this->_maze->get_row() - 1; i >= 0; i --){
	 delete [] this->_displayed[i];
      }
      delete [] this->_displayed;
   }
   delete this->_maze;

   for(std::vector<Maze_Object *>::iterator it = this->_game_objects.begin(); 
	 it != this->_game_objects.end(); it ++){
      delete (*it);
   }
}

void Game::get_display(){
   int row = this->_maze->get_row();
   int col = this->_maze->get_col();
   char ** display = new char * [row];
   for(int i = 0; i < row; i ++){
      display[i] = new char[col];
      for(int j = 0; j < col; j ++){
	 display[i][j] = this->_displayed[i][j];
      }
   }

   for(std::vector<Maze_Object *>::iterator it = this->_game_objects.begin();
	 it != this->_game_objects.end(); it ++){
      if((*it)->get_row() != -1)
	 display[(*it)->get_row()][(*it)->get_col()] = (*it)->get_sym();
   }

   this->_user_interface->set_text(display);
   this->_user_interface->set_score(this->_score);

   for(int i = row - 1; i >= 0; i --){
      delete [] display[i];
   } 
   delete [] display;
}

void Game::set_location(int row, int col, int index){
   int old_row = this->_game_objects.at(index)->get_row();
   int old_col = this->_game_objects.at(index)->get_col();
   this->_game_objects.at(index)->set_location(row, col);
   if(this->_game_objects.at(index)->can_occupy()){
      if(old_row != -1 && old_col != -1)
         this->_maze->at(old_row, old_col)->contains_person_switch();
      if(row != -1 && col != -1)
         this->_maze->at(row,col)->contains_person_switch();
   }
}

void Game::set_location(int row, int col, Maze_Object * pObject){
   int old_row = pObject->get_row();
   int old_col = pObject->get_col();
   pObject->set_location(row, col);
   if(pObject->can_occupy()){
      if(old_row != -1 && old_col != -1)
      this->_maze->at(old_row, old_col)->contains_person_switch();
      if(row != -1 && col != -1)
         this->_maze->at(row,col)->contains_person_switch();
   }
}

void Game::restart(){
   for(std::vector<Maze_Object *>::iterator it = this->_game_objects.begin();
	 it != this->_game_objects.end(); it ++){
      this->set_location(-1, -1, *it);
      (*it)->reset();
   }
   this->_maze->restart();
   this->current_lev_display();
   this->spawn();
   this->get_display();
}
