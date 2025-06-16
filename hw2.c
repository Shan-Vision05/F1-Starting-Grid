/*
*   Commands:
*   
*   ------------- Same as Example ------------
*   Arrow Keys: 
                1. Change View Angle in (Oblique overhead perspective/ orthogonal) 
                2. Navigate the scene in First person perspective
                    (Up and Down arrow) to move forward and backward
                    (left and right arrow) to rotate about the camera axis
*                 
*   0: Reset View Angle
*
*   a/A: Turn Axis on/off
*
*   s/S: View only the Car or View entire scene (acts as a toggle button)
*
*   ESC: Exit
*
*   m/M: swicth between (Oblique Overhead Perspective, Orthogonal and First Person Perspective Projection)
*  
*   +/- : to zoom out/zoom in when in Oblique overhead perspective or First person perspecive
*/

#include "CSCI5229.h"
#include "objects.h"
#include "car.h"

int theta = 20;
int phi = 35;
int dim = 100;

int mode=1;       //  Projection mode
int fov=55;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio

int showCarOnly = 1;
int showAxis = 1;

// First Person perspective Camera states

float  camY = 10;
float camAngle = 0;

float moveStep = 5;
float turnStep = 2;

float Ex, Ey, Ez = 0;




/*
 *
 *  Note: This function is Taken from the example file provided in class.
 *
 */
static void Project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (mode==1 || mode ==2)
        gluPerspective(fov,asp,dim/10,10*dim);
   //  Orthogonal projection
   else
      glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}


void DrawScene()
{
    // Drawing Axis
    double length = 250.0;
    double width = 100.0;
    double side_walk_w = 10.0;

    GridPosMarkers(length, width);

    double wall_width = width/16;


    glEnable(GL_POLYGON_OFFSET_FILL);
    
    glPolygonOffset(1,1);
    Plane(GL_POLYGON, 0,0,0, 0, 0,0, 0.1, 0.1, 0.1, length*2.3, 6*width/7); // Road
    
    glPolygonOffset(2,2);
    Plane(GL_POLYGON, 0,0,0, 0, 0,0, 0.1, 0.5, 0.12, length*2.3, width); // Grass

    glDisable(GL_POLYGON_OFFSET_FILL);

    Plane(GL_POLYGON, -width/2,wall_width/2,0, 0, 0, 90, 0.5,0.5,0.5, length, wall_width); // Side Wall - Left
    Plane(GL_POLYGON, width/2,wall_width/2,0, 0, 0, 90, 0.5,0.5,0.5, length, wall_width); // Side Wall - right

    Plane(GL_POLYGON, width/2+side_walk_w/2, 0, 0, 0,0,0,  0.8, 0.8, 0.8, length, side_walk_w);
    Plane(GL_POLYGON, -(width/2+side_walk_w/2), 0, 0, 0,0,0, 0.2, 0.2, 0.2, length, side_walk_w);


    LightPoles(wall_width, width, length*2);

    GrandStand(length, width, side_walk_w);

    StartLights(length, width);

}

void display()
{
    //  Erase the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //  Enable Z-buffering in OpenGL
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();

    

    if (mode==1) // Oblique overhead perspective;
   {
        Ex = -2*dim* Sin(theta) * Cos(phi);
        Ey = +2*dim * Sin(phi);
        Ez = +2*dim*Cos(theta)*Cos(phi);
        gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(phi),0);
   }
   else if(mode ==2) //First person perspective.
   {

        float dx  =  Sin(camAngle);
        float dz  = -Cos(camAngle);

        gluLookAt(Ex, camY, Ez,
            Ex+dx, camY, Ez+dz,
            0,1,0);

   }
   //  Oblique overhead orthogonal;
   else 
   {
      glRotatef(phi,1,0,0);
      glRotatef(theta,0,1,0);
   }

    if(showCarOnly != 0)
        DrawScene(); // Renders the Scene

    car(); // Renders the car
    
    if(showAxis ==1)
    {
        glColor3f(1,1,1);
        glBegin(GL_LINES);
        glVertex3d(0,0,0);
        glVertex3d(50,0,0);
        glVertex3d(0,0,0);
        glVertex3d(0,50,0);
        glVertex3d(0,0,0);
        glVertex3d(0,0,50);
        glEnd();

        glRasterPos3d(50,0,0);
        Print("X");

        glRasterPos3d(0,50,0);
        Print("Y");

        glRasterPos3d(0,0,50);
        Print("Z");

        
    }

    
    glWindowPos2i(5,5);
    float y_coord = mode!=2? Ey:camY;
    
    Print("View Angle=%d,%d  |  Camera Coordnates: (%.2f,%.2f,%.2f)  |  Mode= %s", phi, theta, Ex, y_coord, Ez,
        mode == 0? "Overhead Orthogonal": mode == 1?"Overhead Perspective":"First Person Perspective");

    ErrCheck("display");
    glFlush();
    glutSwapBuffers();
}


/*
 *  Note: This function is Taken from the ex7.c file provided in class and modified according to my requirement.
 *
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
        if (mode !=2)
        {
        //  Right arrow key - increase azimuth by 5 degrees
        if (key == GLUT_KEY_RIGHT)
            theta += 2;
        //  Left arrow key - decrease azimuth by 5 degrees
        else if (key == GLUT_KEY_LEFT)
            theta -= 2;
        //  Up arrow key - increase elevation by 5 degrees
        else if (key == GLUT_KEY_UP)
            phi -= 2;
        //  Down arrow key - decrease elevation by 5 degrees
        else if (key == GLUT_KEY_DOWN)
            phi += 2;
        }
        else
        {
            if(key==GLUT_KEY_LEFT)  
                camAngle -= turnStep;
            if(key==GLUT_KEY_RIGHT) 
                camAngle += turnStep;
            
            float dx  =  Sin(camAngle)*moveStep;
            float dz  = -Cos(camAngle)*moveStep;
            if(key==GLUT_KEY_UP)
            { 
                Ex += dx; 
                Ez += dz; 
            }
            if(key==GLUT_KEY_DOWN) 
            { 
                Ex -= dx; 
                Ez -= dz; 
            }
        }
        
        //  Keep angles to +/-360 degrees
        theta %= 360;
        phi %= 360;
    //  Tell GLUT it is necessary to redisplay the scengluPerspectivee
    Project();
    
    glutPostRedisplay();
}


/*
 *  Note: This function is Taken from the ex7.c file provided in class.
 *
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{


   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   //  Set projection
   Project();
}

void key(unsigned char ch, int x, int y)
{
    
    if (ch == 27)   //  Exit on ESC
        exit(0);

    
    else if (ch == '0') //  Reset view angle
        {
            theta = 20;
            phi = 35;
        }

    
    else if (ch == 'm' || ch == 'M') //  Switch display mode
    {   if (mode == 2)
        {
            double theta_new   = RAD2DEG(atan2(Ex, Ez)) ;    // degrees
            double phi_new = RAD2DEG(atan2( sqrt(Ex*Ex+Ez*Ez), y)) ; // degrees

            theta = (int)theta_new;
            phi = (int)phi_new ;
        }
        mode = (mode+1)%3;
    }

    else if(ch == 's' || ch =='S')
        showCarOnly = (showCarOnly+1)%2;

    else if(ch == 'a' || ch =='A')
        showAxis = (showAxis+1)%2;
        

    //  Change field of view angle
    else if (ch == '-' && ch>1)
        fov--;
    else if (ch == '+' && ch<179)
        fov++;

    //  Reproject
    Project();
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(900, 900);

    glutCreateWindow("Assignment 2: Shanmukha Vamshi Kuruba");

    #ifdef USEGLEW
    if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
    #endif

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutSpecialFunc(special);

    glutKeyboardFunc(key);

    glutMainLoop();

    return 1;
}