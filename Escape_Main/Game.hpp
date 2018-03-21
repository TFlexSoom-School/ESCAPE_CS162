/*
 * Tristan Hilbert
 * 3/16/18
 * Game Header File
 *
 */

#ifndef __GAME_HPP
#define __GAME_HPP

#include "UI.hpp"
#include "../Maze/Maze.hpp"
#include "../Maze_Objects/Maze_Object.hpp"
#include "../Maze_Objects/Maze_People/Maze_Person.hpp"
#include "../Maze_Objects/Maze_People/Interprid_Student.hpp"

/*
 * Game Class
 * Represents a game of Escape from CS162
 * Only Required methods are the constructors so that it
 *    may assign the UI and use the Maze Object freely
 *
 */

class Game{

   private:
      /* List of all of the objects in a game */
      std::vector<Maze_Object*> _game_objects;

      /* A Pointer to a created Maze Object */
      Maze* _maze;

      /* The Game created character matrix */
      char ** _displayed;

      /* The Game Created score Value */
      int _score;

      /* A Pointer to a User Interface Object 
       * the Game can delegate to a player */
      UI * _user_interface;

      /* A loop that allows for the ability to 
       * catch any exceptions made that completely
       * change the game */
      void try_loop();

      /* Actual loop that can throw exceptions during
       * the game. It should loop until game ends */
      void game_loop();

      /* Shows a skill to all TAs */
      bool show_skill();

      /* Gets all the movement from the people */
      void moves();

      /* Gets the command for the given Maze_Object
       * If applicable to the maze_object */
      void get_command(Maze_Object*);

      /* Checks to see if the given maze_person can make
       * the given move */
      bool get_move(Maze_Person *, char);

      /* Checks the adjacency of the Student to be used
       * before and after its move */
      void check_adjacency(Interprid_Student *);

      /* Spawns the given characters into the map */
      void spawn();

      /* New ups the objects for the Game */
      void create_objects();

      /* Gets the current level and adds it to
       * display */
      void current_lev_display();

      /* Spawns the student at the given indexes */
      void spawn_student(int, int);

      /* Spawns the instructor at the given indexes */
      void spawn_instructor(int, int);

      /* Given the integers for the index along with number
       * of characters left to spawn decide whether or not
       * to spawn a given character  */
      void random_spawn(int, int, int&);

      /* Given the integer constant constraints decides if it
       * is time to spawn the indivual or not */
      bool random_spawn_chance(const int&, const int&, const int&);

      /* Returns whether this is an unoccupied open space */
      bool valid_space(int,int);

      /* Levels up the game and resets all status effects
       * excluding the score */
      void level_up(Maze_Person *);

      /* Sets the location for the given maze object
       * either by pointer address or integer index */   
      void set_location(int, int, Maze_Object*);
      void set_location(int, int, int);

      /* Restarts the game*/
      void restart();

   public:
      /* Constructor */
      Game(Maze*, UI *);

      /* Game Copy Constructor */
      Game(const Game&);

      /* Game Deconstructor */
      ~Game();

      /* Gives UI updated version of display */
      void get_display();

};

#endif
