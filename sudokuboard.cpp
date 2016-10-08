// Implementation file for sudokuboard.h header.
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <fstream>
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

void Board::read_data(const char file_name[])
{
  ifstream in_stream;
  in_stream.open(file_name);
  if (in_stream.fail())
    {
      cout << "Failed to open input file.\n";
      exit(1);
    }
  char next;
  int i = 0, j = 0, cellval = 0;
  while (!in_stream.eof())
    {
      in_stream.get(next);
      // If it's a newline, move i the row indicator forward and reset the col to 0.
      // If not, it's a number from 0 to 9. Input value and shift col indicator forward.
      if (isspace(next))
	{
	  j=0;
	  i++;
	}
      else
	{
	  if (i > 8 || j > 8)
	    {
	      // Something about the text file is not as it seems and has triggered
	      // j to increment to 9. That causes illegal memory access.
	      continue;
	    }
	  cellval = (static_cast<int>(next) - static_cast<int>('0'));
	  sudoku_board[i][j] = cellval;
	  update_possibles(i, j, cellval);
	  j++;
	}
    }
  i = 0; j = 0;
  in_stream.close();
}

ostream& operator <<(ostream& out_stream, const Board& the_object)
{
  int i, j;
  for (i = 0; i < 9; i++)
    for (j = 0; j < 9; j++)
      {
	if (j == 8)
	  {
	    out_stream << the_object.sudoku_board[i][j];
	    out_stream << '\n';
	  }
	else
	  out_stream << the_object.sudoku_board[i][j];
      }
  // Extra line for nicer visuals.
  out_stream << '\n';
  return out_stream;
}

void Board::iterate()
{
  // First try to find all cells with only 1 possible left.
  int i, j, k;
  for (i = 0; i < 9; i++)
    for (j = 0; j < 9; j++)
      {
	// Always needs re-initialization to 0.
	int counter = 0;
	int index = 0;
	// Count the number of possibles and set the index each time.
	for (k = 0; k < 9; k++)
	  {
	    // Counter is counting the number of possibles, i.e. 1s along k's dimension.
	    counter += sudoku_possibles[i][j][k];
	    // If it's a 1, set the index to the index in k's dimension.
	    if (sudoku_possibles[i][j][k] == 1)
	      index = k;
	  }
	if (counter == 0)
	  {
	    cout << "No cell should have NO possibles. Abort!\n";
	    exit(1);
	  }
	else if (counter == 1)
	  {
	    // In that case, the cell has determined its value.
	    // The value is the index recorded during the 3rd nested loop above.
	    sudoku_board[i][j] = index + 1;
	  }
	else
	  {
	    // Not yet solved for the given cell. Do nothing.
	  }
      }
  // Since we have added new values, update the possibles again.
  for (i = 0; i < 9; i++)
    for (j = 0; j < 9; j++)
      {
	int cellvalue = sudoku_board[i][j];
	update_possibles(i, j, cellvalue);
      }
  // Update the solved attribute.
  int counter1 = 0;
  for (i = 0; i < 9; i++)
    for (j = 0; j < 9; j++)
      if (sudoku_board[i][j] > 0)
	counter1++;
  solved = counter1;
  cout << "Total number of solved cells: " << solved << '\n';
  // Now it should be finished. In main() itself, we can output the step-wise
  // solves if we wish.
  // NOTE: slightly inefficient because we can update these things STRICTLY
  // incrementally, e.g. solved should only be calculated as an increment off
  // new entries being added.
}

void Board::update_possibles(int rownum, int colnum, int value)
{
  if (value == 0) return;
  // value refers to the new number filled on the board.
  // If e.g. 9 is newly entered onto the board, we must eliminate the possibility
  // of 9 in all cells on the same row, same col, and same square.
  // FIRST, eliminate all possibles of the actual cell itself:
  for (int k = 0; k < 9; k++)
    {
      // Do not eliminate the possible corresponding to the cell's value itself.
      // Also do not do anything if the value is 0.
      if (k == (value - 1))
	continue;
      else
	{
	  // For all other cells: eliminate!
	  sudoku_possibles[rownum][colnum][k] = 0;
	}
    }
  // SECOND, col-wise elimination:
  for (int i = 0; i < 9; i++)
    {
      // Skip over the actual cell itself. That cell's already been done by FIRST.
      if (i == rownum)
	{
	  continue;
	}
      else
	{
	  // REMEMBER that in sudoku_possibles array, the indexes start at 0 not 1!
	  sudoku_possibles[i][colnum][value - 1] = 0;
	}
    }
  // THIRD, row-wise elimination:
  for (int j = 0; j < 9; j++)
    {
      if (j == colnum)
	{
	  continue;
	}
      else
	sudoku_possibles[rownum][j][value - 1] = 0;
    }
  // FOURTH, square-wise elimination:
  // I need to tell the machine what square it's in.
  // I do that by calculating the row_start and row_end, and col_start and col_end.
  // I have a special exception in innermost loop to do nothing if I hit the exact cell itself.
  int row_start, row_end, col_start, col_end;
  int sq_rownum = rownum / 3; // FLOOR division with both being integers.
  int sq_colnum = colnum / 3;
  row_start = sq_rownum * 3;
  row_end = sq_rownum * 3 + 2;
  col_start = sq_colnum * 3;
  col_end = sq_colnum * 3 + 2;
  for (int i = row_start; i <= row_end; i++)
    for (int j = col_start; j <= col_end; j++)
      {
	// Don't edit the cell itself, this was already done.
	if (i == rownum && j == colnum)
	  continue;
	else
	  sudoku_possibles[i][j][value - 1] = 0;
      }
}
