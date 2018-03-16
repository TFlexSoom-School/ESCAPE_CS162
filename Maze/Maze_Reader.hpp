/*
 * Tristan Hilbert
 * 3/13/18
 * File Reader Header file
 * Takes a file path as an argument and opens and reads the file
 *    into a 2D char array
 *
 */

#ifndef __MAZE_READER_HPP
#define __MAZE_READER_HPP

#include <fstream>
#include <string>

class Maze_Reader{

   private:
      std::ifstream _file_in;
      char*** _content;
      int _n_floors;
      int _rows;
      int _cols;

      void get_dimensions();

   public:
      Maze_Reader(const char*, bool read = true);
      ~Maze_Reader();
      void set_new_path(const char*);
      void read();
      char*** get_content();
      int get_n_floors();
      int get_rows();
      int get_cols();
      
};

#endif
