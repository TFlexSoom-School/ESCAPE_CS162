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
      int score;

      void try_loop();
      void game_loop();
      void update_display();
      void show_skill();
      void moves();
      void spawn();

   public:
      Game(Maze* maze);
      Game(const Game&);
      ~Game();
      void get_display();

};

#endif
