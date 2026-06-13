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
     *   rows: number of rows in the matrix
     *   cols: number of columns in the matrix
     * 
     * Returns:
     *   A pointer to the newly created matrix, or NULL if the creation failed.
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
     *   m: pointer to matrix being freed
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
     *   m: matrix to make a copy of
     * 
     * Returns:
     *   copy: matrix copy of m or NULL if m is invalid
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
     *   dest: variable to store the retrieved value
     *   m: matrix to be accessed
     *   row: row where the desired value is
     *   col: col where the desired value is
     * 
     * Returns:
     *   bool: whether or not the value was successfully retrieved
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
     *   m: matrix to set value in
     *   row: row to place value in
     *   col: col to place value in
     *   value: the value to place in m
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
     *   m: matrix to fill with value "val"
     *   value: value to fill matrix "m" with
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
     *   m: matrix to fill with random values
     *   lower: lower bound (included) of random values
     *   upper: upper bound (included) of random values
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