#include "CSCI5229.h"
#include "objects.h"

int theta = 20;
int phi = 35;
int dim = 150;

int mode=0;       //  Projection mode
int fov=55;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio


// Helper Functions

/*
 *
 *  Note: This function is Taken from the ex.c file provided in class.
 *
 *  Check for OpenGL errors
 */
void ErrCheck(const char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}


static void Project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (mode)
    {
        
        gluPerspective(fov,asp,dim/10,10*dim);
    }
   //  Orthogonal projection
   else
      glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}



void display()
{
    //  Erase the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //  Enable Z-buffering in OpenGL
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();

    if (mode)
   {
      double Ex = -2*dim* Sin(theta) * Cos(phi);
      double Ey = +2*dim        * Sin(phi);
      double Ez = +2*dim*Cos(theta)*Cos(phi);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(phi),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(phi,1,0,0);
      glRotatef(theta,0,1,0);
   }

    

    // Drawing Axis
    double length = 250.0;
    double width = 100.0;
    double side_walk_w = 10.0;

    GridPosMarkers(length, width);

    double wall_width = width/16;

    glEnable(GL_POLYGON_OFFSET_FILL);
    
    glPolygonOffset(1,1);
    Plane(GL_POLYGON, 0,0,0, 0, 0,0, 0.2, 0.2, 0.2, length*2, 6*width/7); // Road
    
    glPolygonOffset(2,2);
    Plane(GL_POLYGON, 0,0,0, 0, 0,0, 0.1, 0.5, 0.12, length*2, width); // Grass

    glDisable(GL_POLYGON_OFFSET_FILL);

    Plane(GL_POLYGON, -width/2,wall_width/2,0, 0, 0, 90, 0.5,0.5,0.5, length, wall_width); // Side Wall - Left
    Plane(GL_POLYGON, width/2,wall_width/2,0, 0, 0, 90, 0.5,0.5,0.5, length, wall_width); // Side Wall - right

    Plane(GL_POLYGON, width/2+side_walk_w/2, 0, 0, 0,0,0, 0.2, 0.2, 0.2, length, side_walk_w);
    Plane(GL_POLYGON, -(width/2+side_walk_w/2), 0, 0, 0,0,0, 0.2, 0.2, 0.2, length, side_walk_w);


    LightPoles(wall_width, width, length*2);

    GrandStand(length, width, side_walk_w);


    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(1,0,0);
    glVertex3d(0,0,0);
    glVertex3d(0,1,0);
    glVertex3d(0,0,0);
    glVertex3d(0,0,1);
    glEnd();

    glRasterPos3d(1,0,0);
    Print("X");

    glRasterPos3d(0,1,0);
    Print("Y");

    glRasterPos3d(0,0,1);
    Print("Z");

    glWindowPos2i(5,5);
    Print("View Angle=%d,%d | Mode=%c", phi, theta, mode? 'p':'o');

    ErrCheck("display");
    glFlush();
    glutSwapBuffers();
}


/*
 *  Note: This function is Taken from the ex7.c file provided in class.
 *
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase azimuth by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      theta += 5;
   //  Left arrow key - decrease azimuth by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      theta -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      phi -= 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      phi += 5;
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
    //  Exit on ESC
   if (ch == 27)
   exit(0);
    //  Reset view angle
    else if (ch == '0')
    theta = phi = 0;
    //  Switch display mode
    else if (ch == 'm' || ch == 'M')
    mode = 1-mode;
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

    glutInitWindowSize(750, 750);

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