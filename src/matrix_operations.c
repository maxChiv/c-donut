/* ---------------------------------------------------------------------------
Written By Max Chivers. 
..Project: C Donut
    matrix_operations.c :
            = the implementation of module for the matrix operations
--------------------------------------------------------------------------- */

#include "matrix_operations.h"

/* Implementations */
/* Creates a struct matrix_t which is initialised with every */
matrix_t* create_matrix(int rows, int cols) {
    // Allocate memory for the matrix struct
    matrix_t* m = (matrix_t*)malloc(sizeof(matrix_t));
    assert(m);

    m->rows = rows;
    m->cols = cols;
    m->data = (double*)malloc(rows * cols * sizeof(double));
    assert(m->data);

    // Assign values
    for (int i = 0; i < m->rows*m->cols; i++) {
        m->data[i] = 0;
    }

    return m;
}

/* Creates a matrix from a given array.
DANGEROUS: Unchecked behaviour and assumes everything input is correct */
matrix_t* arr_2_matrix(double* A, int rows, int cols) {
    assert(A);
    matrix_t* m = (matrix_t*)malloc(sizeof(matrix_t));
    assert(m);
    m->rows = rows;
    m->cols = cols;
    m->data = (double*)malloc(rows * cols * sizeof(double));
    assert(m->data);

    for (int i = 0; i < rows * cols; i++) {
        m->data[i] = A[i];
    }

    return m;
}

/* Returns the value at i`th row and j`th column for matrix m. */
double get_element(matrix_t* m, int i, int j) {
    return m->data[get_index(m, i, j)];
}

/* Frees a given matrix */
void free_matrix(matrix_t* m) {
    free(m->data);
}

/* Returns the appropriate index for the 1D Array implementation for 
i`th row and j`th column for matrix m. */
int get_index(matrix_t* m, int i, int j) {
    return m->cols * i + j;
}

/* Returns the Rotational X Matrix for a 3D matrix. 
- Assumes theta in radians */
matrix_t* Rx_3d(double theta) {
    double A[MATRIX_3D_SIZE * MATRIX_3D_SIZE] = {
        1, 0, 0,
        0, cos(theta), -sin(theta),
        0, sin(theta), cos(theta)
    };
    return arr_2_matrix(A, MATRIX_3D_SIZE, MATRIX_3D_SIZE);
}

/* Returns the Rotational X Matrix for a 3D matrix. 
- Assumes theta in radians */
matrix_t* Ry_3d(double theta) {
    double A[MATRIX_3D_SIZE * MATRIX_3D_SIZE] = {
        cos(theta), 0, sin(theta),
        0, 1, 0,
        -sin(theta), 0, cos(theta)
    };    
    return arr_2_matrix(A, MATRIX_3D_SIZE, MATRIX_3D_SIZE);
}

/* Returns the Rotational X Matrix for a 3D matrix. 
- Assumes theta in radians */
matrix_t* Rz_3d(double theta) {
    double A[MATRIX_3D_SIZE * MATRIX_3D_SIZE] = {
        cos(theta), -sin(theta), 0,
        sin(theta), cos(theta), 0,
        0, 0, 1
    };
    return arr_2_matrix(A, MATRIX_3D_SIZE, MATRIX_3D_SIZE);
}

/* Matrix multiplication: C = A * B
   A: Matrix of size rows_A x cols_A
   B: Matrix of size rows_B x cols_B
   C: Result matrix of size rows_A x cols_B
*/
matrix_t* multiply_matrix(matrix_t* A, matrix_t* B) {
    assert(A->cols == B->rows); // Ensure the matrices are compatible for multiplication

    // Create result matrix C of size A->rows x B->cols
    matrix_t* C = create_matrix(A->rows, B->cols);

    // Perform matrix multiplication
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->cols; j++) {
            double sum = 0;
            for (int k = 0; k < A->cols; k++) {
                sum += get_element(A, i, k) * get_element(B, k, j);
            }
            C->data[get_index(C, i, j)] = sum;
        }
    }

    return C;
}

/* Function to print a matrix */
void print_matrix(matrix_t* m) {
    if (m == NULL || m->data == NULL) {
        printf("Matrix is NULL\n");
        return;
    }

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%lf ", get_element(m, i, j)); // Print each element
        }
        printf("\n"); // New line after each row
    }
}
