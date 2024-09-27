/* ---------------------------------------------------------------------------
Written By Max Chivers. 
..Project: C Donut
    c_donut_operations.h :
            = the header file for the donut operations needed
--------------------------------------------------------------------------- */

#ifndef C_DONUT_OPERATIONS_H
#define C_DONUT_OPERATIONS_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "matrix_operations.h"

#define R1 1.0  // Radius of circle
#define R2 2.0  // Distance from origin
#define K1 5.0  // Controls the scale
#define K2 5.0  // Distance from the viewer 

/* Prototypes */
double torus_x(double theta, double phi);
double torus_y(double theta, double phi);
double torus_z(double theta, double phi);
matrix_t* torus_point(double x, double y, double z);
matrix_t* torus_point_after_rotation(matrix_t* torus_point, double a, double b);
void display_torus_animation();

#endif // C_DONUT_OPERATIONS_H