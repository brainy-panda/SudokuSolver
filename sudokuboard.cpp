// Implementation file for sudokuboard.h header.
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cctype>
#include "sudokuboard.h"
using namespace std;

Board::Board()
{
  // Initializes the board to all 0s and all possibilities are 1 and solved is 0.
  solved = 0;
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      {
	sudoku_board[i][j] = 0;
	for (int k = 0; k < 9; k++)
	  sudoku_possibles[i][j][k] = 1;
      }
}

void Board::read_data(string file_name)
{
  ifstream in_stream;
  in_stream.open(file_name);
  if (in_stream.fail())
    {
      cout << "Failed to open input file.\n";
      exit(1);
    }
  char next;
  int i, j, k;
  while (!in_stream.eof())
    {
      in_stream.get(next);
      // If it's a newline, move i the row indicator forward and reset the col to 0.
      // If not, it's a number from 0 to 9. Input value and shift col indicator forward.
      if (next == '\n')
	j=0; i++;
      else
	{
	  sudoku_board[i][j] = static_cast<int>(next);
	  j++;
	}
    }
  // With the sudoku_board read in from the file, you should now update
  // sudoku_possibles to reflect the known cells.
  update_possibles();
}

ostream& operator <<(ostream& out_stream, const Board the_object)
{
  int i, j;
  for (i = 0; i < 9; i++)
    for (j = 0; j < 9; j++)
      {
	if (j == 9)
	  out_stream << sudoku_board[i][j] << '\n';
	else
	  out_stream << sudoku_board[i][j];
      }
  
}
