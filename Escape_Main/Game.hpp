/*
 * Tristan Hilbert
 * 3/16/18
 * Game Header File
 *
 */

#ifndef __GAME_HPP
#define __GAME_HPP

#include "../Maze/Maze.hpp"
#include "../Maze_Objects/Maze_Object.hpp"

class Game{

   private:
      std::vector<Maze_Object*> _game_objects;
      Maze* _maze;
      char ** _displayed;
      int _score;

      void try_loop();
      void game_loop();
      void update_display();
      void show_skill();
      void moves();
      void spawn();
      void create_objects();
      void current_lev_display();
      void spawn_student(int, int);
      void spawn_instructor(int, int);
      void random_spawn(int, int, int&);
      bool random_spawn_chance(const int&, const int&, const int&);
      void level_up(); /* Don't forget to set positions of objects to -1 -1 */  
   public:
      Game(Maze* maze);
      Game(const Game&);
      ~Game();
      void get_display();

};

#endif
