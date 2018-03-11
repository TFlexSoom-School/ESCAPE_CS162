/*
 * Tristan Hilbert
 * 3/8/18
 * Maze_Level Source File
 *
 */

#include "Maze_Level.hpp"
#include "Wall.hpp"
#include "Open_Space.hpp"
#include "Ladder.hpp"
#include "Student_Spawn.hpp"
#include <iostream>

Maze_Level::Maze_Level(const char** array, int row, int col){
   for(int i = 0; i < row; i ++){
      std::vector<Maze_Location*> vec;
      for(int j = 0; j < col; j ++){
	 switch(array[i][j]){
	    case '#':
	       vec.push_back(new Wall);
	       break;
	    case '@':
	       vec.push_back(new Student_Spawn());
	       break;
	    case '^':
	       vec.push_back(new Ladder());
	       break;
	    case ' ':
	       vec.push_back(new Open_Space());
	       break;
	    default:
	       vec.push_back(new Open_Space());
	       break;
	 }
      }
      this->map.push_back(vec);
   }
}

Maze_Level::~Maze_Level(){
   for(std::vector< std::vector<Maze_Location *> >::iterator it = this->map.begin(); 
	 it != this->map.end(); it ++){

      for(std::vector<Maze_Location *>::iterator jt = it->begin(); jt != it->end(); jt ++){
         delete *jt;
      }
   }
}

Maze_Location* Maze_Level::at(int row, int col){
   return this->map.at(row).at(col);
}

void Maze_Level::display_maze(){
   for(std::vector< std::vector<Maze_Location *> >::iterator it = this->map.begin(); 
	 it != this->map.end(); it ++){

      for(std::vector<Maze_Location *>::iterator jt = it->begin(); jt != it->end(); jt ++){
	 std::cout << (*jt)->get_sym();
      }
      std::cout << std::endl;
   }
}

void Maze_Level::get_spawn(int& r, int& c){
   for(int i = 0; i < this->map.size(); i ++){
      for(int j = 0; j < this->map[i].size(); j ++){
         if(dynamic_cast<Student_Spawn*>(this->map.at(i).at(j)) != NULL){
	    r = i;
	    c = j;
	 }
      }
   }
}
