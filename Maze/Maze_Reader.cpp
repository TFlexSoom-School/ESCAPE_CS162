/*
 * Tristan Hilbert
 * 3/13/18
 * Maze Reader Source File
 *
 */

#include "Maze_Reader.hpp"
#include <iostream>

Maze_Reader::Maze_Reader(const char* file_path, bool read): 
   _file_in(file_path),
   _n_floors(0),
   _rows(0),
   _cols(0),
   _content(NULL)
{
   if(this->_file_in.fail()){
      std::cerr << "The file stream failed" << std::endl;
      this->_file_in.close();
      this->_file_in.clear();
   }else{
      if(read){
	 this->read();
      }
   }
}

Maze_Reader::~Maze_Reader(){
   for(int i = this->_n_floors; i >= 0; i --){
      for(int j = this->_rows; j >= 0; j --){
	 delete [] _content[i][j];
      }
      delete [] _content[i];
   }
   delete _content;
   this->_file_in.close();
}

void Maze_Reader::set_new_path(const char* file_path){
   this->_file_in.open(file_path);
   if(this->_file_in.fail()){
      std::cerr << "The file stream failed" << std::endl;
      this->_file_in.close();
      this->_file_in.clear();
   }
}

void Maze_Reader::read(){
   if(!this->_file_in.is_open()){
      std::cerr << "File stream failed need new file" << std::endl;
      return;
   }
   this->get_dimensions();
   this->_content = new char**[this->_n_floors];
   for(int i = 0; i < this->_n_floors; i ++){
      this->_content[i] = new char*[_rows];
      for(int j = 0; j < this->_rows; j ++){
	 this->_content[i][j] = new char[_cols];
         for(int k = 0; k < this->_cols; k ++){
	    this->_file_in >> this->_content[i][j][k];
	    if(this->_file_in.fail() && k != this->_cols - 1){
	       std::cerr << "File stream did not have required content" << std::endl;
	       this->_file_in.close();
	       this->_file_in.clear();
	       return;
	    }
	 }
      }
   }
}

char*** Maze_Reader::get_content(){
   if(_content != NULL)
      return this->_content;
   return NULL;
}

int Maze_Reader::get_n_floors(){
   return this->_n_floors;
}

int Maze_Reader::get_rows(){
   return this->_rows;
}

int Maze_Reader::get_cols(){
   return this->_cols;
}

void Maze_Reader::get_dimensions(){
   this->_file_in >> this->_n_floors;
   this->_file_in >> this->_rows;
   this->_file_in >> this->_cols;
   if(this->_file_in.fail()){
      std::cerr << "File could not make it past dimensions" << std::endl;
      this->_file_in.close();
      this->_file_in.clear();
   }
}
