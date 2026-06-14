#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "matrix.h"

/*
 * Lifecycle methods
 */

Matrix *matrix_create(int rows, int cols) {
    /*
     * Parameters:
     *   rows (int): number of rows in the matrix
     *   cols (int): number of columns in the matrix
     * 
     * Returns:
     *   (Matrix*): a pointer to the newly created matrix, or NULL if the creation failed.
     */

    // Edge case: invalid (non-positive) dimensions
    if (rows <= 0 || cols <= 0) {
        return NULL;
    }

    // Set up the matrix
    Matrix *m = malloc(sizeof(Matrix));
    if (m == NULL) {
        fprintf(stderr, "matrix_create: malloc failed\n");
        return NULL;
    }

    m->rows = rows;
    m->cols = cols;

    m->data = calloc(rows * cols, sizeof(double));\
    if (m->data == NULL) {
        fprintf(stderr, "matrix_create: calloc failed\n");
        free(m);
        return NULL;
    }

    // Return the matrix pointer
    return m;
}


void matrix_free(Matrix *m) {
    /*
     * Parameters:
     *   m (Matrix*): pointer to matrix being freed
     * 
     * Returns:
     *   N/A 
     */

    if (m != NULL) {
        free(m->data);
        free(m);
    }
}


Matrix *matrix_copy(const Matrix *m) {
    /*
     * Parameters:
     *   m (Matrix*): matrix to make a copy of
     * 
     * Returns:
     *   copy (Matrix*): matrix copy of m or NULL if m is invalid
     */

    // Edge case: m is invalid
    if (m == NULL) {
        return NULL;
    }

    Matrix *copy = matrix_create(m->rows, m->cols);
    memcpy(copy->data, m->data, m->rows * m->cols * sizeof(double));

    return copy;
}

/*
 * Element access methods
 */

bool matrix_get(double *dest, const Matrix *m, int row, int col) {
    /*
     * Parameters:
     *   dest (double*): variable to store the retrieved value
     *   m    (Matrix*): matrix to be accessed
     *   row  (int)    : row where the desired value is
     *   col  (int): col where the desired value is
     * 
     * Returns:
     *   (bool): whether or not the value was successfully retrieved
     */

    // Edge case: m is invalid
    if (m == NULL) {
        return false;
    }

    // Edge case: row or col are invalid
    if (row < 0 || col < 0 || row >= m->rows || col >= m->cols) {
        return false;
    }

    // Extract the value and return success
    *dest = m->data[row * m->cols + col];
    return true;
}


bool matrix_set(Matrix *m, int row, int col, double value) {
    /*
     * Parameters:
     *   m     (Matrix*): matrix to set value in
     *   row   (int)    : row to place value in
     *   col   (int)    : col to place value in
     *   value (double) : the value to place in m
     * 
     * Returns:
     *   bool: whether or not the value was successfully set
     * 
     */

    // Edge case: m is invalid
    if (m == NULL) {
        return false;
    }

    // Edge case: row or col are invalid
    if (row < 0 || col < 0 || row >= m->rows || col >= m->cols) {
        return false;
    }

    // Set the value and return success
    m->data[row * m->cols + col] = value;
    return true;
}

/*
 * Pre-filling methods
 */

void matrix_fill(Matrix *m, double value) {
    /*
     * Parameters:
     *   m     (Matrix*): matrix to fill with value "val"
     *   value (double) : value to fill matrix "m" with
     * 
     * Returns:
     *   N/A
     */

     // Edge case: m is invalid
     if (m == NULL) {
        return;
     }

     // Fill the matrix
     int mat_size = m->rows * m->cols;
     for (int index = 0; index < mat_size; index++) {
        m->data[index] = value;
     }
}


void matrix_rand(Matrix *m, double lower, double upper) {
    /*
     * Parameters:
     *   m     (*Matrix): matrix to fill with random values
     *   lower (double) : lower bound (included) of random values
     *   upper (double) : upper bound (included) of random values
     * 
     * Returns:
     *   N/A
     */

    // Edge case: m is invalid
    if (m == NULL) {
        return;
    }

    // Edge case: lower is not actually the lower bound
    if (lower >= upper) {
        return;
    }

    // Fill with random values
    int mat_size = m->rows * m->cols;
    for (int index = 0; index < mat_size; index++) {
        double rand_value = ((double) rand() / RAND_MAX) * (upper - lower) + lower;
        m->data[index] = rand_value;
    }
}

/*
 * Math operation methods
 */


Matrix *matrix_add(const Matrix* a, const Matrix *b) {
    /*
     * Parameters:
     *   a (Matrix*): first matrix to be added
     *   b (Matrix*): second matrix to be added
     * 
     * Returns:
     *   result (Matrix*): result of a + b
     */

    // Edge case: either matrix is invalid
    if (a == NULL || b == NULL) {
        return NULL;
    }

    // Edge case: matrices aren't of same shape
    if (a->rows != b->rows || a->cols != b->cols) {
        return NULL;
    }

    // Create and fill new matrix
    Matrix *result = matrix_create(a->rows, a->cols);

    int mat_size = a->rows * a->cols;
    for (int index = 0; index < mat_size; index++) {
        result->data[index] = a->data[index] + b->data[index];
    }

    return result;
}


Matrix *matrix_sub(const Matrix *a, const Matrix *b) {
    /*
     * Parameters:
     *   a (Matrix*): matrix to subtract from
     *   b (Matrix*): matrix to subtract from a with
     * 
     * Returns:
     *   result (Matrix*): result of a - b
     */

    // Edge case: either matrix is invalid
    if (a == NULL || b == NULL) {
        return NULL;
    }

    // Edge case: matrices aren't of same shape
    if (a->rows != b->rows || a->cols != b->cols) {
        return NULL;
    }

    // Create and fill new matrix
    Matrix *result = matrix_create(a->rows, a->cols);

    int mat_size = a->rows * a->cols;
    for (int index = 0; index < mat_size; index++) {
        result->data[index] = a->data[index] - b->data[index];
    }

    return result;
}


Matrix *mat_mult(const Matrix *a, const Matrix *b) {
    /*
     * Parameters:
     *   a (Matrix*): first (left) matrix to multiply
     *   b (Matrix*): second (right) matrix to multiply
     * 
     * Returns:
     *   result (Matrix*): result of standard matrix mutliplication AB
     */

    // Edge case: either matrix is invalid
    if (a == NULL || b == NULL) {
        return NULL;
    }

    // Edge case: dimensions don't match
    if (a->cols != b->rows) {
        return NULL;
    }

    // Create the matrix
    Matrix *result = matrix_create(a->rows, b->cols);

    // Go through each position in the result
    int mat_size = a->rows * b->cols;
    for (int index = 0; index < mat_size; index++) {
        int row_index = index / b->cols;
        int col_index = index % b->cols;

        // Note that the length of a row in a is equal to a->cols,
        // which is also equal to the height of a col in b
        for (int k = 0; k < a->cols; k++) {
            result->data[index] += a->data[row_index * a->cols + k] * b->data[k * b->cols + col_index];
        }
    }

    return result;
}