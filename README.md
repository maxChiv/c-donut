# ASCII 3D Torus Renderer - (c-donut)

This application renders a 3D rotating torus (donut shape) as an ASCII animation. The program uses the math behind matrix multiplication and trigonometric functions to rotate the torus along three axes (X, Y, Z) and display it in real-time within a terminal.

## Table of Contents

1. [Features](#features)
2. [How It Works](#how-it-works)
3. [Prerequisites](#prerequisites)
4. [Directory Structure](#directory-structure)
5. [Installation](#installation)
6. [Configuration](#configuration)
7. [Troubleshooting](#troubleshooting)
8. [Acknowledgements](#acknowledgements)
9. [Limitations, Challenges and Future Improvements](#limitations-challenges-and-future-improvements)

## Features

- Real-time ASCII rendering of a 3D rotating torus.
- Rotation along X, Y, and Z axes.
- Adjustable screen width, height, and frame rate.
- Utilizes matrix transformations to compute 3D points on the torus.
- Implements ASCII shading based on the angle of each point relative to the viewer.

## How It Works

1. **3D Coordinates**: The cross-sectional points of the torus are defined as a circle and transformed into 3D space.
2. **Rotation**: The program applies rotation matrices (`Rx`, `Ry`, `Rz`) to simulate rotation along the X, Y, and Z axes.
3. **Projection**: After rotation, 3D coordinates are projected into 2D screen space for rendering.
4. **ASCII Shading**: The brightness of each point is determined based on its orientation relative to a light source and is represented by different ASCII characters.
5. **Rendering**: The result is printed to the terminal in a grid format, simulating the 3D rotation of the torus.

## Prerequisites

- C compiler (e.g., GCC)
- Terminal with a minimum recommended screen size of 80x24 (but works with different sizes)

## Directory Structure 
```
/c-donut
├── Makefile                        # Makefile for building the project
├── src                             # Source files for the data structure implementation
    ├── c_donut_operations.h        # Header file for the donut operations
    ├── c_donut_operations.c        # Implementation file for the donut operations
    ├── matrix_operations.c         # Implementation file for the matrix operations
    ├── matrix_operations.h         # Header file for the matrix operations
    ├── driver.c                    # Location of main 
└── tests                           # Directory containing test files
    ├── matrix_operations_tests.c   # Unit tests for the matrix implementation
└── example                         # Directory containing example file
    ├── c_donut_example.c           # An example source code of the original 
└── docs                            # Directory containing document files
    ├── C Donut Notes.pdf           # The hand writing notes used to understand the math 
```

## Installation

1. Clone the repository or download the source files.
    ```bash
    git clone https://github.com/maxChiv/c-donut.git
    ```

2. Compile and run the program using `gcc` and the Makefile target:
    ```bash
    make run
    ```

## Configuration

- **Screen Size**: You can adjust the screen width and height in the source code:
    ```c
    int screen_width = 80;  // Change this for different terminal widths
    int screen_height = 24;  // Change this for different terminal heights
    ```
- **Rotation Speed**: To control the rotation speed, modify the angle increments in the main loop:
    ```c
    theta += 0.04;  // Change the step size for smoother or faster rotation
    ```

## Troubleshooting

- If the torus appears distorted or misaligned, try adjusting your terminal window size or tweaking the screen width and height in the source code.
- Ensure your terminal supports the necessary screen size (80x24 or larger) for proper rendering.

## Acknowledgements

Inspired by donut.c by Andy Sloane and other ASCII rendering projects.  
[https://www.a1k0n.net/2011/07/20/donut-math.html](https://www.a1k0n.net/2011/07/20/donut-math.html)

With help from Torus - Wiki  
[https://en.wikipedia.org/wiki/Torus](https://en.wikipedia.org/wiki/Torus)

---

## Limitations, Challenges and Future Improvements

1. When writing this program, I initially wanted to implement the matrix rotations and thus find the 3D coordinates of the torus by doing matrix arithmetic. However, the problem was the inaccuracy of the matrix arithmetic, yielding very inaccurate coordinates. 
    - In the future, I would like to implement this logic using matrix operations, as it would allow more flexibility in the program, allowing for differing rotations by choice of the user:
        ``` 
        > Which axis is the 'axis of revolution': x 
        > Rotate along the y axis (Y/N): N
        > Rotate along the z axis (Y/N): Y
        ```
    - Note: The hardcoded values are based on Andy Sloane's math for the rendering, so the default is: the axis of revolution is Y, and both other axes are rotating.
  
2. The hardcoded values seen in `c_donut_operations.c` in most functions that do trigonometry yield more accurate results and smoother resolution. It is not typically the coding practice I follow; however, it works in this instance and I want to fix it one day. 
