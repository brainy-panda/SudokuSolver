This program solves Sudoku problems (or determines if they are impossible).


Algorithm:

This solver uses a recursive backtracking algorithm with some exploitation of low-hanging fruit as opposed to the naive recursive backtracking algorithm.

Basically, the solver finds the cell with the lowest number of possible entries. It then tries a value (or the value, if it is only 1 possible entry) for that cell.

Then it proceeds to another cell and tries a value.

At any point when it tries a value, the way the recursive function is specified makes it "remember" where it tried that value. It will backtrack to the mistaken value and try a next value.

You can think of this algorithm as traversing a tree with a depth-first search.


Compilation on a Windows machine using MinGW: g++ sudokuboard.cpp solver.cpp -o solver.exe

Makefile:

sudoku: sudokuboard.cpp solver.cpp
	g++ -o solver.exe sudokuboard.cpp solver.cpp
clean:
	rm -f sudoku
