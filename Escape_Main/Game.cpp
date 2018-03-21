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

/* Constructor */
/* Both Arguments should be previously constructed */
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

/* Copy Constructor */
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

/* Deconstructor */
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

/*
 * create_objects()
 * creates the objects for the game to be used until deconstruction
 * post: Objects will be created and pushed back in
 *          into the vector based on the Z-Order of the display
 */
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

/*
 * try_loop()
 * A code segment to catch all thrown exceptions for game changes
 */
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

/*
 * game_loop()
 * the actual game loop for the game object
 * may throw exceptions
 */
void Game::game_loop(){
   do{
      this->get_display();
      this->moves();
   }while(true);
}

/*
 * current_lev_display()
 * Updates display variable by extracting it from the maze object
 * post: displayed may be deleted and renewed
 */
void Game::current_lev_display(){
   if(this->_displayed != NULL){
      for(int i = this->_maze->get_row() - 1; i >= 0; i --){
	 delete [] this->_displayed[i];
      }
      delete [] this->_displayed;
   }

   this->_displayed = this->_maze->get_current_lev();
}

/* 
 * show_skill()
 * shocks all the TAs in the game
 * post: all TAs will be "shocked"
 * return: whether the player can shock the TAs
 */
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

/*
 * moves()
 * represents a turn in the game. this occurs each round
 * post: display may be changed along with certain _game_objects
 *
 */
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

/* 
 * check_adjacency(Interprid_Student*)
 * gives the row and collumn of the student to each object to let
 *    the object use its game functionality
 * param: pointer to the student object within the game.
 * pre: pStudent is new upped
 * post: score may be changed
 *
 */
void Game::check_adjacency(Interprid_Student * pStudent){
   for(std::vector<Maze_Object*>::iterator it = this->_game_objects.begin(); 
	 it != this->_game_objects.end(); it++){
      (*it)->adjacent_check(pStudent->get_row(), pStudent->get_col(), this->_score);
   }
}

/*
 * get_command(Maze_Object *)
 * Checks to see it the object has the right to
 *    establish itself in a new place
 * pre: Maze_Object is defined with an object on the heap
 * post: Maze_Object may have a new location
 */
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

/*
 * get_move(Maze_Person *, char)
 * returns whether this person wants to move to
 *    an actual valid space and moves them there if so
 * pre: pPerson is a new upped object and command is wasd
 * post: pPerson may have a new location as delegated aswell to the maze
 * return: if pPerson moved
 */
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

/*
 * valid_space(int,int)
 * checks if the given space based on index is a valid
 *    new position for a given person
 * return: the given space is open and unnoccupied
 */
bool Game::valid_space(int row, int col){
   if(this->_maze->valid_space(row, col)){
      return true;
   }
   return false;
}

/*
 * spawn()
 * sets the locations of all the game_objects based
 *    on set character spawn points or random spawning
 * post: Game objects will have new set locations
 *
 */
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

/*
 * random_spawn(int, int, int)
 * delegated for random spawning based on given integer info
 * param: row, col of spawning and integer of objects left to spawn
 * post: An object may or may not spawn at the given space
 */
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

/*
 * random_spawn_chance(int,int,int)
 * decides if the an object should spawn based on the given constraints
 * returns: based on superhuman mathematical models if spawning should occur
 *
 */

bool Game::random_spawn_chance(const int& row, const int& col,const int& number_spawn){
   int modulus = row * this->_maze->get_col();
   modulus = (this->_maze->get_row() * this->_maze->get_col()) - modulus;
   return (rand() % modulus <= this->_game_objects.size() - number_spawn); /* Chance increases as spots left decreases */
}

/*
 * spawn_student(int, int)
 * spawns the student at the given row and col
 * param: row and col of spawn
 * post: Interprid_Student objects will have their location
 *          set to arguments
 */
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

/*
 * spawn_instructor(int,int)
 * spawns the Instructor at the given row and col
 * param: row and col of spawn
 * post: Instructor objects will have their location 
 *       set to arguments
 */
 *
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

/*
 * level_up(Maze_person *)
 * param: argument of someone trying to up the level
 * pre: pPerson is an interprid student preferablly
 * post: Maze will be leveled and maze will have a new display
 *          depending on if level up was valid. Essentially the
 *          game starts anew with uninitialized locations so
 *          spawning must occur
 */
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

/*
 * get_display()
 * this horribly named function allocates
 *    a char matrix for the display of the board
 *    then sends it to the UI.
 * post: a new array will be allocated on the heap then
 *       deallocated. the matrix is of size level_row level_col
 */
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

/*
 * set_location(int,int,int)
 * Sets the location of the object at the specified index
 *    also allowing maze to have correct occupied switches
 * param: row and col of placement and index of _game_object vector
 * pre: _game_object[index] is a defined Maze_Object * pointing to a
 *      continaer on the heap
 * post: _game_object[index] will have a new location and maze_locations
 *          within the current level of maze will have been switched for
 *          occupied state.
 */
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

/*
 * set_location(int,int,Maze_Object *)
 * Sets the location of the object also allowing maze to have 
 *    correct occupied switches
 * param: row and col of placement and pointer to Maze_Object
 * pre: pObject is a defined Maze_Object * pointing to an
 *       object on the heap
 * post: *pObject will have a new location and maze_locations
 *          within the current level of maze will have been switched for
 *          occupied state.
 */
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

/*
 * restart()
 * restarts the game back at 0
 * post: All game statistcs will be pushed back to as
 *          if the game was ready just after spawn
 */
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
   this->_score = 0;
}
