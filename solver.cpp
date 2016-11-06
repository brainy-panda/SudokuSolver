#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "sudokuboard.h"
using namespace std;

int main() {
  Board sudoku;
  char inputfile[80];
  cout << "Welcome to the Sudoku Solver!\n";
  cout << "Please enter the name of the file which contains the initial Sudoku board!\n";
  cout << "Enter file name: > ";
  cin >> inputfile;
  cout << "Thank you. Loading initial Sudoku board now.\n";
  sudoku.read_data(inputfile);
  cout << "The initial board looks like this:\n\n";
  cout << sudoku;
  Sleep(2000);
  cout << "The solver is beginning to solve. Please stand by.\n";
  if (sudoku.recursive_solve()) {
    cout << "The board has a solution:\n";
    cout << sudoku;
  } else {
    cout << "A solution could not be found.\n";
  }
  cout << "Enter anything to end this program.\n";
  char dummy;
  cin >> dummy;
  return 0;
}
