#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "../src/matrix_operations.h"   // Include the matrix operations implementation

// Function to compare two double values for approximate equality
int approx_equal(double a, double b, double epsilon) {
    return fabs(a - b) < epsilon;
}

// Unit test for creating a matrix
void test_create_matrix() {
    matrix_t* m = create_matrix(3, 3);
    assert(m != NULL);
    assert(m->rows == 3);
    assert(m->cols == 3);
    for (int i = 0; i < m->rows * m->cols; i++) {
        assert(m->data[i] == 0);
    }
    free_matrix(m);
}

// Unit test for getting an element from a matrix
void test_get_element() {
    double A[9] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    matrix_t* m = arr_2_matrix(A, 3, 3);
    assert(approx_equal(get_element(m, 0, 0), 1, 1e-9));
    assert(approx_equal(get_element(m, 1, 1), 5, 1e-9));
    assert(approx_equal(get_element(m, 2, 2), 9, 1e-9));
    free_matrix(m);
}

// Unit test for matrix multiplication
void test_multiply_matrix() {
    double A_data[9] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    double B_data[9] = {
        9, 8, 7,
        6, 5, 4,
        3, 2, 1
    };

    matrix_t* A = arr_2_matrix(A_data, 3, 3);
    matrix_t* B = arr_2_matrix(B_data, 3, 3);
    matrix_t* C = multiply_matrix(A, B);

    // Expected result of A * B
    double expected_data[9] = {
        30, 24, 18,
        84, 69, 54,
        138, 114, 90
    };
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assert(approx_equal(get_element(C, i, j), expected_data[i * 3 + j], 1e-9));
        }
    }

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

// Unit test for rotational matrices
void test_rotation_matrices() {
    double theta = M_PI / 2; // 90 degrees

    // Test Rx
    matrix_t* Rx = Rx_3d(theta);
    double expected_Rx[9] = {
        1, 0, 0,
        0, 0, -1,
        0, 1, 0
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assert(approx_equal(get_element(Rx, i, j), expected_Rx[i * 3 + j], 1e-9));
        }
    }
    free_matrix(Rx);

    // Test Ry
    matrix_t* Ry = Ry_3d(theta);
    double expected_Ry[9] = {
        0, 0, 1,
        0, 1, 0,
        -1, 0, 0
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assert(approx_equal(get_element(Ry, i, j), expected_Ry[i * 3 + j], 1e-9));
        }
    }
    free_matrix(Ry);

    // Test Rz
    matrix_t* Rz = Rz_3d(theta);
    double expected_Rz[9] = {
        0, -1, 0,
        1, 0, 0,
        0, 0, 1
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assert(approx_equal(get_element(Rz, i, j), expected_Rz[i * 3 + j], 1e-9));
        }
    }
    free_matrix(Rz);
}
/*
int main(int argc, char const *argv[]) {
    test_create_matrix();
    test_get_element();
    test_multiply_matrix();
    test_rotation_matrices();
    printf("All tests passed!\n");
    return 0;
}
*/