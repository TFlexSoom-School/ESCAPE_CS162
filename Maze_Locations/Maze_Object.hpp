/*
 * Tristan Hilbert
 * 3/8/18
 * Person Header File
 *
 */


#ifndef __MAZE_OBJECT_HPP
#define __MAZE_OBJECT_HPP

class Maze_Object{
   private:
      int _row;
      int _col;

   public:
      Maze_Object(int, int);
      void set_location(int, int);
      int get_row();
      int get_col();
      virtual bool can_occupy() =0;
};


#endif
