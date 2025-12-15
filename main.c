
/*
VPL-friendly main:
Input format (recommended):
size
then size*size integers (row by row)

Output:
- "MAGIC" or "NOT_MAGIC"
- If not magic, tries fixSingleCell and prints:
  "FIXED" and the matrix, or "CANNOT_FIX"
*/
int main(void) {
    int size;
    if (scanf("%d", &size) != 1) return 0;

    int matrix[MAX_SIZE][MAX_SIZE];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    if (isMagicSquare(size, matrix)) {
        printf("MAGIC\n");
        return 0;
    }

    printf("NOT_MAGIC\n");

    int res = fixSingleCell(size, matrix);
    if (res == 1) {
        printf("FIXED\n");
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                printf("%d%s", matrix[i][j], (j == size - 1) ? "": " ");
            }
            printf("\n");
        }
    } else {
        printf("CANNOT_FIX\n");
    }

    return 0;
}
