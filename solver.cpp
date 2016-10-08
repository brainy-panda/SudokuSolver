#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "sudokuboard.h"
using namespace std;

// Define a class for the Sudoku Board.
// Class Board should have member functions:
// 1. Constructor.
// 2. Read the data from an external file (puzzle.csv).
// 3. Overloaded out-stream operator <<(outstream, object).
// 4. Perform a single iteration of finding new entries.
// 5. Eliminate possibilities after a new cell value has been entered.
// Thus, step (2) should call 2(a) 9 times, 2(b) 9 times, and 2(c) 9 times.
// The Board should have the following attributes:
// 1. A 9-by-9 2-d array showing the values. 0 means it is still unsolved.
// 2. An integer showing how many squares are currently solved.
// 3. A 9-by-9-by-9 3-d array showing which numbers are still POSSIBLE for a given square.
//    Where only 1 number is possible, the square is solved and its value is set to the correct value.

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
