# magic-square
C implementation for validating magic squares and correcting an almost-magic square by fixing a single incorrect cell.

# Magic Square Checker + Single-Cell Fix (C)

This project implements three functions for working with **magic squares**:

1. `calcDiagonalSums(size, matrix)`  
2. `isMagicSquare(size, matrix)`  
3. `fixSingleCell(size, matrix)`  

A **magic square** here means:
- All **row sums** are equal
- All **column sums** are equal
- The **main diagonal** sum equals that same value
- The **secondary diagonal** sum equals that same value

## Files
- `main.c` (or whatever you name it): contains the full solution and a simple test `main()`.

## Functions

### `int calcDiagonalSums(int size, int matrix[size][size])`
- Computes the sum of the main diagonal and the secondary diagonal.
- Returns the diagonal sum if both diagonals match.
- Returns `0` if they do not match.

### `int isMagicSquare(int size, int matrix[size][size])`
- Returns `1` if the matrix is a magic square.
- Returns `0` otherwise.
- Uses `calcDiagonalSums()` as the target sum for rows/cols.

### `int fixSingleCell(int size, int matrix[size][size])`
Attempts to fix an **almost magic square** by changing exactly **one** cell.

Return values:
- `size` if the matrix is already a magic square
- `1` if a single-cell change successfully fixes it
- `0` if it cannot be fixed under the “single bad cell” assumption

Assumption:
- Exactly one row sum and one column sum are wrong, and the wrong cell is at their intersection.
```bash
gcc -std=c11 -O2 -Wall -Wextra -pedantic main.c -o magic
