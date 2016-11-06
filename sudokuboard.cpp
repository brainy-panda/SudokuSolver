// Implementation file for sudokuboard.h header.

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include "sudokuboard.h"
using namespace std;

Board::Board()
{
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      sudoku_board[i][j] = 0;
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
      if (isspace(next))
	{
	  j=0;
	  i++;
	}
      else
	{
	  if (i > 8 || j > 8)
	    {
	      // The eof() flag is not set until you actually pass the end, causing
	      // j to increment to 9. That causes illegal memory access and weird shit happens.
	      continue;
	    }
	  cellval = (static_cast<int>(next) - static_cast<int>('0'));
	  sudoku_board[i][j] = cellval;
	  j++;
	}
    }
  i = 0; j = 0;
  in_stream.close();
}

ostream& operator <<(ostream& out_stream, const Board& the_object)
{
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      {
	if (j == 8)
	  {
	    out_stream << the_object.sudoku_board[i][j];
	    out_stream << '\n';
	  }
	else
	  out_stream << the_object.sudoku_board[i][j];
      }
  out_stream << '\n';
  return out_stream;
}

bool Board::is_complete()
{
  int count_blanks = 0;
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      {
	if (sudoku_board[i][j] == 0)
	  count_blanks++;
      }
  // cout << "is_complete() found " << count_blanks << " blanks.\n";
  if (count_blanks == 0)
    return true;
  else
    return false;
}

void Board::find_next_cell(int& row, int& col)
{
  // Note that this finds a cell with the MINIMUM number of possible values.
  // In many cases this will be 1 possible case, which means that the solver will enter a correct value.
  // This reduces the number of backtrackings in a typical solve.
  // In other cases, there might be 2 possible cases, which is good odds that we get lucky.
  int possibles[9][9];
  int min_possibles = 999;
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      possibles[i][j] = 0;
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      {
	for (int k = 1; k <= 9; k++)
	  if (try_cell(i, j, k, false))
	    possibles[i][j]++;
	if (possibles[i][j] < min_possibles && possibles[i][j] > 0)
	  min_possibles = possibles[i][j];
      }
  // if (min_possibles > 1) {
  //   cout << "Reached a fork with " << min_possibles << " possibles at row " << row << " col " << col << ".\n";
  // }
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      {
	if (sudoku_board[i][j] == 0 && possibles[i][j] == min_possibles) {
	  row = i; col = j;
	  return;
	}
      }
}

void Board::erase_cell(int row, int col) { sudoku_board[row][col] = 0; }

bool Board::recursive_solve()
{
  if (is_complete())
    return true;
  int row = 0, col = 0;
  find_next_cell(row, col);
  for (int val = 1; val <= 9; val++)
    {
      if (try_cell(row, col, val, true))
	{
	  // cout << "Writing into row " << row << " col " << col << " value " << val << ".\n";
	  if (recursive_solve())
	    return true;
	  // cout << "Backtracking to erase the value " << val << " at row " << row << " col " << col << ".\n";
	  erase_cell(row, col);
	}
    }
  return false;
}

bool Board::try_cell(int row, int col, int value, bool write)
{
  if (sudoku_board[row][col] > 0)
    return false;
  int rowwise_cntr = 0, colwise_cntr = 0, squarewise_cntr = 0;
  for (int j = 0; j < 9; j++)
    {
      if (sudoku_board[row][j] == value)
  	rowwise_cntr++;
      if (sudoku_board[j][col] == value)
  	colwise_cntr++;
    }
  int sq_rowstart = (row / 3) * 3;
  int sq_colstart = (col / 3) * 3;
  int sq_rowend = (row / 3) * 3 + 2;
  int sq_colend = (col / 3) * 3 + 2;
  for (int i = sq_rowstart; i <= sq_rowend; i++)
    for (int j = sq_colstart; j <= sq_colend; j++)
      {
  	if (sudoku_board[i][j] == value)
  	  squarewise_cntr++;
      }
  if ((rowwise_cntr + colwise_cntr + squarewise_cntr) > 0)
    return false;
  else
    {
      if (write) { sudoku_board[row][col] = value; }
      return true;
    }
}
