/* ---------------------------------------------------------------------------
Written By Max Chivers. 
..Project: C Donut
    c_donut_operations.c :
            = the implementation of module for the donut operations needed
--------------------------------------------------------------------------- */

#include "c_donut_operations.h"

/* Implementations */

/* ------------------------------------------------------------------------ */
/*NOTE ALL TORUS POINTS ARE BASED ON ROTATION AROUND Y AXIS */
double torus_x(double theta, double phi) {
    return (R2 + R1 * cos(theta)) * cos(phi);
}

double torus_y(double theta, double phi) {
    return R1 * sin(theta);
}

double torus_z(double theta, double phi) {
    return -(R2 + R1 * cos(theta)) * sin(phi);
}
/* ------------------------------------------------------------------------ */

matrix_t* torus_point(double x, double y, double z) {
    double coords[3] = {x, y, z};
    return arr_2_matrix(coords, 3, 1);
}

matrix_t* torus_point_after_rotation(matrix_t* torus_point, double a, double b) {
    /* Rotates around x-axis by a and z-axis by b */
    
    // Create rotation matrices
    matrix_t* Rx = Rx_3d(a);  // Rotation matrix around x-axis
    matrix_t* Rz = Rz_3d(b);  // Rotation matrix around z-axis

    // Multiply the matrices
    matrix_t* rotated_x = multiply_matrix(Rx, torus_point);
    matrix_t* rotated_result = multiply_matrix(Rz, rotated_x);

    // Free the intermediate rotation matrix
    free(Rx);
    free(rotated_x);
    free(Rz);

    return rotated_result; // Return the final rotated matrix
}

void display_torus_animation() {
    float A = 0, B = 0;
    float i, j;
    int k;
    float z[1760];
    char b[1760];

    printf("\x1b[2J");
    for (;;) {
        memset(b, 32, 1760);
        memset(z, 0, 7040);

        for (j = 0; j < 6.28; j += 0.07) {
            for (i = 0; i < 6.28; i += 0.02) {
                // Calculate the torus point in 3D
                double x_coord = torus_x(i, j);
                double y_coord = torus_y(i, j);
                double z_coord = torus_z(i, j);

                // Convert to a matrix representation
                matrix_t* point = torus_point(x_coord, y_coord, z_coord);
                
                // Rotate the point
                matrix_t* rotated_point = torus_point_after_rotation(point, A, B);
                
                // Extract the rotated coordinates
                double rotated_x = rotated_point->data[0];  // Accessing the x coordinate
                double rotated_y = rotated_point->data[1];  // Accessing the y coordinate
                double D = 1 / (rotated_x * 0.5 + rotated_y * 0.5 + K2);  // Simplified distance calculation
                int x_proj = (int)(40 + 30 * D * (rotated_x));
                int y_proj = (int)(12 + 15 * D * (rotated_y));

                // Use shading for ASCII representation
                int o = x_proj + 80 * y_proj;
                int N = 8 * ((rotated_y) * (0.5) - rotated_x);
                
                if (22 > y_proj && y_proj > 0 && x_proj > 0 && 80 > x_proj && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }

                // Clean up the rotated point matrix
                free(point);
                free(rotated_point);
            }
        }

        printf("\x1b[H");
        for (k = 0; k < 1761; k++) {
            putchar(k % 80 ? b[k] : 10);
        }

        A += 0.04;  // Increment rotation angle A
        B += 0.02;  // Increment rotation angle B
        usleep(30000);  // Delay for animation effect
    }
}