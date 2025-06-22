# F1-Starting-Grid
An OpenGL demo rendering a 3D Formula 1 starting grid with detailed car models, track markings and dynamic lighting.

Homework 2 Shanmukha_Vamshi : 3D Scene 

Shanmukha Vamshi Kuruba
CSCI5229 Summer 2025

Key bindings

    Arrow Keys: 
                1. Change View Angle in (Oblique overhead perspective/ orthogonal) 
                2. Navigate the scene in First person perspective
                    (Up and Down arrow) to move forward and backward
                    (left and right arrow) to rotate about the camera axis
                 
    0: Reset View Angle

    a/A: Turn Axis on/off

    s/S: View only the Car or View entire scene (acts as a toggle button)

    ESC: Exit

    m/M: swicth between (Oblique Overhead Perspective, Orthogonal and First Person Perspective Projection)
  
    +/- : to zoom out/zoom in when in Oblique overhead perspective or First person perspecive

Instructions to Run:

    Navigate to the directory with the source code and run 

    1. make

    2. ./hw2

Aknowlegments:

    1. The imports were taken from example. Didn't make any modifications as it had all the header files i needed.

    2. ErrCheck(const char*) : void, Taken from  example.

    3. Print(const char* format, ...): void, Taken form  example.

    4. special(int, int, int): void, taken from  example.

    5. reshape(int, int): void, taken from and modified the dim value to fit my View.

    6. I've referred to https://www.geeksforgeeks.org/dsa/cubic-bezier-curve-implementation-in-c/ for Bezier curve concept. What differs from the website, they only implemented for 3 control points. I have created a for loop to work for any number of points.

    7. Most of the fuctions have the basic building blocks inspired from examples

Code Structure:

    1. The main entry point is the hw2.c, this is where all the objects are called and rendered.

    2. objects.c has all the scene related object creation code.

    3. car.c has all the car related object creation code.

    4. print.c has the function to print to the window.

    5. errcheck.c has the function to catch errors.

Time Taken for this assigment: ~ 20+ Hours (including all kinds of formatting, Trial & Error)