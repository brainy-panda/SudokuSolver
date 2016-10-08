// Header file SudokuBoard.h.
#ifndef BOARD_H
#define BOARD_H

using namespace std;

class Board
{
public:
  Board();
  // Constructor to initialize everything correctly.
  void read_data(const char file_name[]);
  // This should read data from a file, whose name is specified.
  friend ostream& operator <<(ostream& outs, const Board& the_object);
  // This is an overloaded operator for out stream to output data.
  void iterate();
  // This should perform one iteration of eliminating possibilities and thus
  // populating empty cells when a given cell has only one possibility.
  void update_possibles(int rownum, int colnum, int value);
  // Updates the sudoku_possibles 3d array and the attribute 'solved'.
  // This should be INCREMENTAL: edit the possibles 3d matrix with each new entry.
  // For the initial reading in of the board, simply call this function every time
  // we encounter a new value from the input file.
  // This function is equivalent to filling in a cell by hand and reducing the
  // possibilities for other cells in the same row / col / square.
  int solved;
  // The number of cells solved. 81 cells solved means a solved board.
private:
  int sudoku_board[9][9];
  // Known values on the board represented as 9-by-9 matrix.
  int sudoku_possibles[9][9][9];
  // A 3-dimensional matrix with 1s and 0s:
  // The 3rd dimension represents whether each number is a 'possible candidate'
  // for the given cell. For example, Row 2, Col 3 might have a KNOWN value of 9.
  // In that case, sudoku_possibles[1][2][9] == 1 but sudoku_possibles[1][2][n] == 0
  // for n from 1 to 8. Because only 9 is a possible candidate and no others.
};

#endif
