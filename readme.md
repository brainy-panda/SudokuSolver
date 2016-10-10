This program solves sudoku problems. The problem should be written into the puzzle.dat file, with 0s in every blank cell.

Note: it cannot solve "hard" Sudoku problems in which there are bottlenecks where no particular blank cell has a unique possible value but a set of 2, 3, ... etc. cells share the same possibles and can thus eliminate others in the same row/col/square as them.

Compilation on a Windows machine using MinGW: g++ sudokuboard.cpp solver.cpp -o solver.exe