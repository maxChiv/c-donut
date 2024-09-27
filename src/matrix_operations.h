/* ---------------------------------------------------------------------------
Written By Max Chivers. 
..Project: C Donut
    matrix_operations.h :
            = the interface of module for the matrix operations
--------------------------------------------------------------------------- */
#ifndef MATRIX_OPERATIONS_H  // Check if MATRIX_OPERATIONS_H is not defined
#define MATRIX_OPERATIONS_H  // Define MATRIX_OPERATIONS_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

#define MATRIX_3D_SIZE 3

/* Prototypes */

typedef struct {
    int rows;
    int cols;
    double* data;  // 1D array for matrix of doubles for ok accuracy
} matrix_t;

/* Function Prototypes */
matrix_t* create_matrix(int rows, int cols);
double get_element(matrix_t* m, int i, int j);
int get_index(matrix_t* m, int i, int j);
void free_matrix(matrix_t* m);
matrix_t* arr_2_matrix(double* A, int rows, int cols);
matrix_t* multiply_matrix(matrix_t* A, matrix_t* B);
void print_matrix(matrix_t* m);
matrix_t* Rx_3d(double theta);
matrix_t* Ry_3d(double theta);
matrix_t* Rz_3d(double theta);


#endif