#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "sudokuboard.h"
using namespace std;

int main() {
  // Declare Board object.
  Board sudoku;
  // First to read the file.
  char inputfile[80];
  cout << "Welcome to the Sudoku Solver!\n";
  cout << "Please enter the name of the file which contains the initial Sudoku board!\n";
  cout << "Enter file name: > ";
  cin >> inputfile;
  cout << "Thank you. Loading initial Sudoku board now.\n";
  sudoku.read_data(inputfile);
  // Now display the board to the user.
  cout << "The initial board looks like this:\n\n";
  cout << sudoku;
  Sleep(2000);
  // Now begin solving.
  cout << "The solver is beginning to solve. Please stand by.\n";
  int iteration = 1;
  while (sudoku.solved < 81)
    {
      cout << "Solver iteration " << iteration << ":\n\n";
      sudoku.iterate();
      iteration++;
      cout << "The board now looks like this:\n\n";
      cout << sudoku;
      Sleep(1000);
    }
  // If the while loop completes, then the solver has done its dirty work.
  cout << "Congratulations! The Sudoku Solver has successfully finished solving.\n";
  cout << "Enter anything to end this program.\n";
  char dummy;
  cin >> dummy;
  return 0;
}
