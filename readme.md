This program solves sudoku problems. The problem should be written into the puzzle.dat file, with 0s in every blank cell.

Note: it cannot solve "hard" Sudoku problems in which there are bottlenecks where no particular blank cell has a unique possible value but a set of 2, 3, ... etc. cells share the same possibles and can thus eliminate others in the same row/col/square as them.

Algorithm:

This solver proceeds by iteratively REMOVING POSSIBLES and POPULATING CELLS.

A POSSIBLE indicates that a given cell could possibly be this value: it has not yet been ruled out. Therefore a blank cell must have 2 or more possibles.

CELL POPULATION occurs when there is one and only one possible in the cell: then the value is filled in.

Every CELL POPULATION triggers a REMOVING POSSIBLES according to the three rules of Sudoku:

1. No same-row cell may have the same value.

2. No same-col cell may have the same value.

3. No same-square cell may have the same value.

Iterating these two main procedures will solve all 'simple' Sudoku problems.

Algorithm for "hard" problems:

4. Add to REMOVING POSSIBLES several new rules:

4(a): Find within the same row, col, or square if two cells have the identical set of two POSSIBLES.
      If they do, then for the row, col, or square that this pair of cells share, eliminate those two POSSIBLES from all other cells.

4(b): Find within the same row, col, or square if THREE cells have identical set of THREE possibles. ...

4(c): Find within the same row, col, or square if FOUR cells have identical set of FOUR possibles. ...

... I am unsure at this point if you need to search for quintuples (if they even exist in real games, even hard ones) of identical POSSIBLES sets in the same row / col / square.

Compilation on a Windows machine using MinGW: g++ sudokuboard.cpp solver.cpp -o solver.exe