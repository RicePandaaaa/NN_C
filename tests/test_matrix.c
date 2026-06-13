#include <stdio.h>

#include "matrix.h"

int main() {
    // Test creation
    printf("--- Creation Test ---\n");
    Matrix *m = matrix_create(3, 4);
    printf("Rows: expecting 3, got %d\n", m->rows);
    printf("Cols: expecting 4, got %d\n", m->cols);

    // Test set/get
    printf("\n--- Set/Get Test ---\n");
    double val;
    matrix_set(m, 0, 0, 1.5);
    matrix_set(m, 2, 3, 9.9);
    matrix_get(&val, m, 0, 0);
    printf("m[0][0]: expecting 1.5, got %.1f\n", val);
    matrix_get(&val, m, 2, 3);
    printf("m[2][3]: expecting 9.9, got %.1f\n", val);

    // Test bounds checking
    printf("\n--- Bounds Test ---\n");
    printf("set(-1,0): expecting false (0), got %d\n", matrix_set(m, -1, 0, 1.0));
    printf("get(3,0):  expecting false (0), got %d\n", matrix_get(&val, m, 3, 0));

    // Test copy
    printf("\n--- Copy Test ---\n");
    Matrix *copy = matrix_copy(m);
    matrix_get(&val, copy, 0, 0);
    printf("copy[0][0]: expecting 1.5, got %.1f\n", val);

    // Free
    printf("\n--- Freeing Test ---\n");
    matrix_free(m);
    matrix_free(copy);
    printf("Run 'make valgrind' to confirm no leaks\n");

    return 0;
}