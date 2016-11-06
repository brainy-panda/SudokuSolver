// Header file SudokuBoard.h.
#ifndef BOARD_H
#define BOARD_H

#include <fstream>
#include <iostream>

using namespace std;

class Board
{
public:
  Board();
  void read_data(const char file_name[]);
  friend ostream& operator <<(ostream& outs, const Board& the_object);
  bool recursive_solve(); // Recursive function solves all classes of sudoku problems.
  bool is_complete();
 private:
  bool try_cell(int row, int col, int value, bool write);
  void erase_cell(int row, int col);
  void find_next_cell(int& row, int& col);  
  int sudoku_board[9][9];
};

#endif
