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
      virtual ~Maze_Object();
      void set_location(int, int);
      int get_row();
      int get_col();
      void adjacent_check(int, int, int&);
      virtual bool random_spawn();
      virtual bool can_occupy() =0;
      virtual void reset() =0;
      virtual char get_sym() =0;
      virtual void adjacent(int&, bool same_space = false) =0;

};


#endif
