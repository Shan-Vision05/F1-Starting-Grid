#include "CSCI5229.h"

int theta = 20;
int phi = 35;
int dim = 85;

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

static void Plane(int type, 
    double x, double y, double z,
    double th, double pi, double ro,
    double r, double g, double b,
    double h, double w)
{
    glPushMatrix();

    glTranslated(x, y, z);
    glRotated(pi, 1, 0, 0);
    glRotated(th, 0, 1, 0);
    glRotated(ro, 0, 0, 1);

    glColor3f(r, g, b);
    glBegin(type);
    glVertex3f(-w/2,0,h/2);
    glVertex3f(w/2,0,h/2);
    glVertex3f(w/2, 0, -h/2);
    glVertex3f(-w/2,0,-h/2);
    glEnd();

    glPopMatrix();

}

static void cube(double x,double y,double z,
    double dx,double dy,double dz,
    double th)
{
//  Save transformation
glPushMatrix();
//  Offset
glTranslated(x,y,z);
glRotated(th,0,0,1);
glScaled(dx,dy,dz);
//  Cube
glBegin(GL_QUADS);
//  Front
glColor3f(1,0,0);
glVertex3f(-1,-1, 1);
glVertex3f(+1,-1, 1);
glVertex3f(+1,+1, 1);
glVertex3f(-1,+1, 1);
//  Back
glVertex3f(+1,-1,-1);
glVertex3f(-1,-1,-1);
glVertex3f(-1,+1,-1);
glVertex3f(+1,+1,-1);
//  Right
glVertex3f(+1,-1,+1);
glVertex3f(+1,-1,-1);
glVertex3f(+1,+1,-1);
glVertex3f(+1,+1,+1);
//  Left
glVertex3f(-1,-1,-1);
glVertex3f(-1,-1,+1);
glVertex3f(-1,+1,+1);
glVertex3f(-1,+1,-1);
//  Topfrom image
glVertex3f(-1,+1,+1);
glVertex3f(+1,+1,+1);
glVertex3f(+1,+1,-1);
glVertex3f(-1,+1,-1);
//  Bottom
glVertex3f(-1,-1,-1);
glVertex3f(+1,-1,-1);
glVertex3f(+1,-1,+1);
glVertex3f(-1,-1,+1);
//  End
glEnd();
//  Undo transformations
glPopMatrix();
}

static void LightPole(double x,double y,double z,double r, double h, char side)
{
//    const int d=15;

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(r,1.0,r);

   glColor3f(0, 0, 1);

//    int ph = 0;

    glBegin(GL_QUAD_STRIP);
    for (int th=0;th<=360;th+=30)
    {
            glVertex3d(Cos(th),h,Sin(th));
            glVertex3d(Cos(th),0,Sin(th));
    }
    glEnd();
    

    //  Undo transformations
    glPopMatrix();

    int head_size = h/4;
    int head_angle = 70;

    int x_offset = -Sin(head_angle)*head_size/2 + 0.25;
    int y_offset = h + Cos(head_angle)*head_size/2;

    if (side == 'r')
        cube(x_offset+x, y_offset+y,z, 0.25,head_size/2,head_size/4,70);
    else
        cube(-x_offset+x, y_offset,z, 0.25,head_size/2,head_size/4,110);
}

static void LightPoles(double wall_w, double road_w, double road_l)
{
    for(int z = -road_l/2; z< road_l/2;z+=30)
    {
        LightPole(road_w/2+1,0,z, 0.25, wall_w*4, 'r');
        LightPole(-(road_w/2+1),0,z, 0.25, wall_w*4, 'l');
    }
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
    double length = 200.0;
    double width = 50.0;
    double side_walk_w = 10.0;

    double wall_width = width/8;

    Plane(GL_POLYGON, 0,0,0, 0, 0,0, 0.2, 0.2, 0.2, length, 3*width/4); 
    
    

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1,1);
    Plane(GL_POLYGON, 0,0,0, 0, 0,0, 0.1, 0.5, 0.12, length, width); // Road + Grass

    glDisable(GL_POLYGON_OFFSET_FILL);

    Plane(GL_POLYGON, -width/2,wall_width/2,0, 0, 0, 90, 0.5,0.5,0.5, length, wall_width); // Side Wall - Left
    Plane(GL_POLYGON, width/2,wall_width/2,0, 0, 0, 90, 0.5,0.5,0.5, length, wall_width); // Side Wall - right

    Plane(GL_POLYGON, width/2+side_walk_w/2, 0, 0, 0,0,0, 0.2, 0.2, 0.2, length, side_walk_w);
    Plane(GL_POLYGON, -(width/2+side_walk_w/2), 0, 0, 0,0,0, 0.2, 0.2, 0.2, length, side_walk_w);


    LightPoles(wall_width, width, length);
    // LightPole(width/2+1,0,0, 0.25, 40);
    // LightPole(-(width/2+1),0,0, 0.25, 40);
    
    // LightPole(-(width/2+1),0,0, 0.25, 40);

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