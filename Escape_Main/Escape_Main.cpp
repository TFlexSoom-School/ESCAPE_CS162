/*
 * Tristan Hilbert
 * 3/15/18
 * Escape Main Source File
 *
 * escape [FilePathArg]
 * Escape from CS162 is a game designed by Dr. Rob Hess which
 *    takes place on a grid like board with user designed levels.
 * The game only requires a path argument to a text file that is orientated
 *    based on the following specs:
 *    It must have the following values at the first line of the file
 *    [Number_Of_Floors] [Number_Of_Rows] [Number_Of_Columns] like so:
 *    3 5 5
 *    This will make a 3 floor maze with 5 by 5 grids
 * The following should be text based on the legend below:
 *  # = Wall
 *    = Open Space (Whitespace char)
 *  @ = Player Spawn
 *  ^ = Ladder Location (1 needed on all floors excluding last floor)
 *  % = Instructor Location (1 needed on last floor)
 * Any other character will be defaulted into a whitespace(openspace) character
 *
 * In-Game the controls work as such:
 * w or up_arrow = up 1 square
 * d or right_arrow = right 1 square
 * s or down_arrow = down 1 square
 * a or left_arrow = left 1 square
 * p = use of programming skill (Freezes all T characters)
 * u = use of ladder (If applicable) to go up a level
 *
 * The goal is to avoid becoming adjacent to T characters, Gain 3 $
 *    by landing on those squares and reach to top level to approach
 *    the % (Instructor)
 *
 * Good Luck and have fun. Other Features may be added to the game but will be
 * described in "Reflect.txt"
 *
 */
#include <cstring>
#include <iostream>

#include "../Maze/Maze.hpp"
#include "../Maze/Maze_Reader.hpp"
#include "Game.hpp"
#include "UI.hpp"

/* Main Method */
int main(int argc, char* argv[]){
   if(argc != 2 || !strcmp(argv[1],"-h") || !strcmp(argv[1], "--help")){
      std::cout << "Please use the following format\n"
	 << "./escape maze.txt"
	 << std::endl;
   }else if(strstr(argv[1], ".txt") == NULL){
      std::cerr << "Argument is not a .txt file. ERROR" << std::endl;
   }else{
      Maze_Reader* read = new Maze_Reader(argv[1]);
      if (read->get_content() == NULL){
	 delete read;
         return 1;
      }
      Maze* maze = new Maze(read->get_content(), read->get_n_floors(), read->get_rows(), read->get_cols());
      UI* user = new UI(read->get_rows(), read->get_cols());
      Game* game = new Game(maze, user);
      
      delete game;
      delete user;
      delete read;
   }
   return 0;
}
