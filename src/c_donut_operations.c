/* ---------------------------------------------------------------------------
Written By Max Chivers. 
..Project: C Donut
    c_donut_operations.c :
            = the implementation of module for the donut operations needed
--------------------------------------------------------------------------- */

#include "c_donut_operations.h"

/* Implementations */

/* ------------------------------------------------------------------------ */
/* Finding the inital cross sectional circle  */
double circle_x(double theta) {
    return (R2 + R1 * cos(theta));
}

double circle_y(double theta) {
    return R1 * sin(theta);
}

/* ------------------------------------------------------------------------ */

/* Function to get rotated coords of a point on torus based on the cross-sectional circle, 
phi (angle to rotate around axis of revolution), A rotation around axis X, and B rotation around axis B 
returning the new coordinates
Note yxz is order of rotational angles */
double* rotate_circle_yxz(double circle_x, double circle_y, double phi, double A, double B) {
    // Precompute sine and cosine of angles for efficiency
    double cosA = cos(A), sinA = sin(A);
    double cosB = cos(B), sinB = sin(B);
    double cosphi = cos(phi), sinphi = sin(phi);
    
    // Allocate memory for the rotated coordinates (3 doubles)
    double* rotated_coords = (double*)malloc(3 * sizeof(double));
 
    // Apply the rotation formulas for x, y, and z coordinates
    rotated_coords[0] = circle_x * (cosB * cosphi + sinA * sinB * sinphi) - circle_y * cosA * sinB;
    rotated_coords[1] = circle_x * (sinB * cosphi - sinA * cosB * sinphi) + circle_y * cosA * cosB;
    rotated_coords[2] = cosA * circle_x * sinphi + circle_y * sinA;
    
    return rotated_coords;
}

void display_torus_animation() {
    int screen_width = 80; 
    int screen_height = 24;
    // Calculate respective K1
    // const double aspect_ratio = screen_width/(double)screen_height;
    double K1x = screen_width/2;
    double K1y = screen_height/2;

    double A = 0, B = 0;  // Rotational Angles along two axes
    double theta, phi;
    int k;
    double zbuffer[screen_height * screen_width];  // Z buffer of 1D array representing the entire screen
    char output_buffer[screen_height * screen_width];  // The output we first place in before printing it

    for (;;) {
        memset(output_buffer, 32, screen_height * screen_width);  // Fill the ASCII buffer with spaces (' ' = 32 in ASCII)
        memset(zbuffer, 0.0, screen_height * screen_width * sizeof(double));   // Fill the depth buffer 'z' with zeros

        for (theta = 0; theta < 6.28; theta += 0.07) {
            for (phi = 0; phi < 6.28; phi += 0.02) {
  
                double circlex = circle_x(theta);
                double circley = circle_y(theta);

                double* rotated_coords = rotate_circle_yxz(circlex, circley, phi, A, B);

                // Save the 3D coords of the torus
                double x = rotated_coords[0];
                double y = rotated_coords[1];
                double z = rotated_coords[2];

                double ooz = 1 / (K2 + z);  // "one over z"

                // x and y projection.  note that y is negated here, because y
                // goes up in 3D space but down on 2D displays.
                int x_proj = (int)((screen_width/2 + K1x*ooz*x));
                int y_proj = (int)((screen_height/2 - K1y*ooz*y));

                // Clamp the projection to be on screen
                x_proj = (x_proj < 0) ? 0 : (x_proj >= screen_width ? screen_width - 1 : x_proj);
                y_proj = (y_proj < 0) ? 0 : (y_proj >= screen_height ? screen_height - 1 : y_proj);

                // calculate luminance.  ugly, but correct. (based on normal surface against direction of light)
                    // L ranges from -sqrt(2) to +sqrt(2).  If it's < 0, the surface
                    // is pointing away from us, so we won't bother trying to plot it.
                double L = cos(phi)*cos(theta)*sin(B) - cos(A)*cos(theta)*sin(phi) - sin(A)*sin(theta) + cos(B)*(cos(A)*sin(theta) - cos(theta)*sin(A)*sin(phi));

                if (L > 0) {
                    // test against the z-buffer. Larger 1/z means the pixel is closer
                    int i_buffer = x_proj + y_proj * screen_width;  // Calculate the buffer index
                    assert(i_buffer >= 0 && i_buffer < screen_width * screen_height);
                    if(ooz > zbuffer[i_buffer]) {
                        zbuffer[i_buffer] = ooz;
                        int i_luminance = L*8;  // Calculate luminance index ( 0-sqrt(2) -> 0-11[index])
                        // Output the buffer char at the position 
                        output_buffer[i_buffer] = LUMINANCE_CHARS[i_luminance];
                    }
                }                
            }
        }

        for (k = 0; k < (screen_height*screen_width+1); k++) {
            putchar(k % screen_width ? output_buffer[k] : 10);
        }

        A += 0.04;  // Increment rotation angle A
        B += 0.02;  // Increment rotation angle B
        usleep(30000);  // Delay for animation effect
    }
}