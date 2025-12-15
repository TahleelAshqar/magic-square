#include <stdio.h>

#define MAX_SIZE 10

int calcDiagonalSums(int size, int matrix[size][size]) {
    int mainSum = 0, secSum = 0;

    for (int i = 0; i < size; i++) {
        mainSum += matrix[i][i];
        secSum  += matrix[i][size - 1 - i];
    }

    return (mainSum == secSum) ? mainSum : 0;
}

int isMagicSquare(int size, int matrix[size][size]) {
    int target = calcDiagonalSums(size, matrix);
    if (target == 0) return 0;

    for (int i = 0; i < size; i++) {
        int rowSum = 0;
        int colSum = 0;

        for (int j = 0; j < size; j++) {
            rowSum += matrix[i][j];
            colSum += matrix[j][i];
        }

        if (rowSum != target || colSum != target) return 0;
    }

    return 1;
}

static void computeRowColSums(int size, int matrix[size][size], int rowSums[], int colSums[]) {
    for (int i = 0; i < size; i++) {
        rowSums[i] = 0;
        colSums[i] = 0;
        for (int j = 0; j < size; j++) {
            rowSums[i] += matrix[i][j];
            colSums[i] += matrix[j][i];
        }
    }
}

static int majorityTarget(int size, int sums[]) {
    // In the “almost magic” case: n-1 are equal, 1 differs.
    // Return the value that appears at least 2 times (works for n>=3).
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (sums[j] == sums[i]) count++;
        }
        if (count >= 2) return sums[i];
    }
    return sums[0]; // fallback (shouldn't be needed for valid cases)
}

int fixSingleCell(int size, int matrix[size][size]) {
    if (isMagicSquare(size, matrix)) {
        return size;
    }

    int rowSums[MAX_SIZE], colSums[MAX_SIZE];
    computeRowColSums(size, matrix, rowSums, colSums);

    int targetRow = majorityTarget(size, rowSums);
    int targetCol = majorityTarget(size, colSums);

    // For a valid “single row + single column wrong” scenario, these targets should match.
    // If they don't, still attempt using the row-majority as target (more conservative).
    int target = targetRow;

    int badRow = -1, badCol = -1;
    int badRowCount = 0, badColCount = 0;

    for (int i = 0; i < size; i++) {
        if (rowSums[i] != target) {
            badRow = i;
            badRowCount++;
        }
        if (colSums[i] != target) {
            badCol = i;
            badColCount++;
        }
    }

    if (badRowCount != 1 || badColCount != 1) {
        return 0;
    }

    int delta = target - rowSums[badRow];

    // Column must also be fixed by the same delta (same cell intersection)
    if (colSums[badCol] + delta != target) {
        return 0;
    }

    int oldVal = matrix[badRow][badCol];
    matrix[badRow][badCol] = oldVal + delta;

    // Verify it truly becomes a magic square (rows, cols, and both diagonals)
    if (isMagicSquare(size, matrix)) {
        return 1;
    }

    // Revert if not successful
    matrix[badRow][badCol] = oldVal;
    return 0;
}
