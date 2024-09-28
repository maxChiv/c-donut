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

#define R1 1  // Radius of circle
#define R2 2.0  // Distance from origin
#define K1 8.0;  // A typical choice for ASCII art representations
#define K2 5.0  // Distance from the viewer 
#define LUMINANCE_CHARS ".,-~:;=!*#$@"


/* Prototypes */
double circle_x(double theta);
double circle_y(double theta);
double* rotate_circle_yxz(double circle_x, double circle_y, double phi, double A, double B);
void display_torus_animation();

#endif // C_DONUT_OPERATIONS_H