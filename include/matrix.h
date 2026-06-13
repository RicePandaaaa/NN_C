#include <stdbool.h>

#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int rows;
    int cols;
    double *data;
} Matrix;


/* Methods for life cycle management */
Matrix *matrix_create(int row, int cols);
void    matrix_free(Matrix *m);
Matrix *matrix_copy(const Matrix *src);

/* Methods for elements */
bool   matrix_get(double *dest, const Matrix *m, int row, int col);
bool   matrix_set(Matrix *matrix, int row, int col, double value);

/* Methods for pre-filling */
void   matrix_fill(Matrix *m, double value);
void   matrix_rand(Matrix *m, double lower, double upper);

/* Methods for math operations */
Matrix *matrix_add(const Matrix *a, const Matrix *b);
Matrix *matrix_sub(const Matrix *a, const Matrix *b);
Matrix *matrix_mult(const Matrix *a, const Matrix *b);
Matrix *matrix_scale(const Matrix *m, double scalar);
Matrix *matrix_transpose(const Matrix *m);
Matrix *matrix_hadamard(const Matrix *a, const Matrix *b);

/* Methods for debugging */
void   matrix_print(const Matrix *m);

#endif // MATRIX_H