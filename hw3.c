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
*   c/C: View only the Car or View entire scene (acts as a toggle button)
*
*   ESC: Exit
*
*   m/M: swicth between (Oblique Overhead Perspective, Orthogonal and First Person Perspective Projection)
*  
*   +/- : to zoom out/zoom in when in Oblique overhead perspective or First person perspecive
*
*   a/A : to decrease and increase Ambient Lighting respectively
*  
*   s/S : to decrease and increase Specular Lighting respectively
*
*   d/D : decrease and increase Diffusion Lighting respectively
*
*   e/E : decrease and increase Emmitance Lighting respectively
*
*   n/N : decrease and increase Shininess respectively
*
*   i/I : to turn on/off the lighting
*
*   y/Y: to decrease and increase the height of light source respectively
*
*   w/W: to decrease and increase the movement of light in X direction
*
*   l/L: to decrease and increase the movement of light in Z direction
*
*   ' ': Space bar press will stop the light at it's current position
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

// First Person perspective Camera states
float  camY = 1;
float camAngle = 0;

float moveStep = 5;
float turnStep = 2;

float Ex, Ey, Ez = 0;

// Lighting Pareameters

int light = 1;
float ambient = 40.0;
float diffuse = 30.0;
float specular = 50.0;
float emission = 0;
float shiny = 0;
int shininess =   0;  

float zh = 90.0;
float ylight =35.0;
float distance = 50.0;

float light_z = 3.5;
float light_x = 1.3;

int move = 1;
unsigned int texture[13]; // Texture names



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

/*
 *  Note: This function is Taken from the example file provided in class.
 *  Draw vertex in polar coordinates with normal
 */
void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

/*
 *  Note: This function is inspired from the example file provided in class.
 */
static void ball(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball with yellow specular
   float white[]   = {1.0,1.0,1.0,1.0};
   float Emission[] = {0.01*emission,0.01*emission,0.01*emission,1.0};
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   int inc = 15;
   for (int ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}


void DrawScene()
{
    glPushMatrix();
    // Drawing Axis
    double length = 250.0;
    double width = 100.0;
    double side_walk_w = 10.0;

    double road_width = 6*width/7;

    
    glScaled(0.1, 0.1, 0.1);
    glTranslated(-2*width-width/2, 0, 0);

    GridPosMarkers(0,0,0, length, width, texture[2]);
    GridPosMarkers(0,0,0, length, width, texture[2]);

    double wall_width = width/16;


    glEnable(GL_POLYGON_OFFSET_FILL);
    
    glPolygonOffset(1,1);
    Plane(GL_POLYGON, 0,0,0, 0, 0,0, 1, 1, 1, length*2.3, road_width, texture[0], 10, 20, 1); // Road
    Plane(GL_POLYGON, 4*width+road_width,0,0, 0, 0,0, 1, 1, 1, length*2.3, road_width, texture[0], 10, 20, 1);
    Arc(2*width+road_width/2, 0, -length*2.3/2, 2*width, 2*width + road_width, 180, 360, texture[0]);
    Arc(2*width+road_width/2, 0, length*2.3/2, 2*width, 2*width + road_width, 180, 0, texture[0]);

    double pitLane_ir = road_width - side_walk_w;

    Plane(GL_POLYGON, road_width - side_walk_w ,0,0, 0, 0,0, 1, 1, 1, length*2, road_width/4, texture[0], 10, 20, 1); //Pit Lane
    Arc(5*(pitLane_ir) + road_width/8, 0, -length*2/2, 4*pitLane_ir, 4*pitLane_ir + 20, 180, 240, texture[0]);
    Arc(7*(pitLane_ir) + road_width/8, 0, length*2/2, 6*pitLane_ir, 6*pitLane_ir + 20, 180, 150, texture[0]);

    
    
    glPolygonOffset(2,2);
    Plane(GL_POLYGON, 0,0,0, 0, 0,0, 0.1, 0.5, 0.12, length*5, width, texture[1], 12, 20, 1); // Grass
    Plane(GL_POLYGON, 4*width+width,0,0, 0, 0,0, 0.1, 0.5, 0.12, length*5, width, texture[1], 12, 20, 1); // Grass
    Plane(GL_POLYGON, 2*width+width/2,0,0, 0, 0,0, 0.1, 0.5, 0.12, length*5, 4*width, texture[1], 12, 20, 1);

    glDisable(GL_POLYGON_OFFSET_FILL);

    Plane(GL_POLYGON, -width/2,wall_width/2,0, 0, 0, 90, 0.5,0.5,0.5, length, wall_width,texture[3], 1, 15, 0); // Side Wall - Left
    Plane(GL_POLYGON, width/2,wall_width/2,0, 0, 0, 90, 0.5,0.5,0.5, length, wall_width, texture[3], 1, 15, 1); // Side Wall - right

    Plane(GL_POLYGON, width/2+side_walk_w/2, 0, 0, 0,0,0,  0.2, 0.2, 0.2, length, side_walk_w, texture[2], 2, 15, 1);
    Plane(GL_POLYGON, -(width/2+side_walk_w/2), 0, 0, 0,0,0, 0.2, 0.2, 0.2, length, side_walk_w, texture[2], 2, 15, 1);


    LightPoles(wall_width, width, length*2, texture[4], texture[5]);

    GrandStand(length, width, side_walk_w, texture[4], texture[2], texture[5], 4*width + road_width);

    StartLights(length, width, texture[5], texture[6]);

    Garages(road_width,0,0, 20, texture[4]);

    car(texture[7], texture[8], texture[9], texture[10], texture[11], texture[12]); 

    glPopMatrix();

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


    // Adding Lighting to the scene
    glShadeModel(GL_SMOOTH);
    if (light==1)
    {
        float Ambient[] = {0.01*ambient, 0.01*ambient, 0.01*ambient, 1.0 };
        float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
        float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
        //  Light position
        float Position[]  = {light_x*distance*Cos(zh),ylight, light_z*distance*Sin(zh),1.0};
        
        glColor3f(1,1,1);
        ball(Position[0],Position[1],Position[2] , 1);
        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        //  glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        //  Enable light 0
        glEnable(GL_LIGHT0);
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
        glLightfv(GL_LIGHT0,GL_POSITION,Position);
    }
    else
        glDisable(GL_LIGHTING);

    if(showCarOnly != 0)
        DrawScene(); // Renders the Scene
    // Garages(0,0,0, 20, texture[5]);
    

    // glPushMatrix();
    // glScaled(0.1, 0.1, 0.1);
    // // Renders the car
    // glPopMatrix();


    // Disabling lighting for axis
    glDisable(GL_LIGHTING);
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

    glWindowPos2i(5,5);
    float y_coord = mode!=2? Ey:camY;
    
    Print("View Angle=%d,%d  |  Camera Coordnates: (%.2f,%.2f,%.2f)  |  Mode= %s", phi, theta, Ex, y_coord, Ez,
        mode == 0? "Overhead Orthogonal": mode == 1?"Overhead Perspective":"First Person Perspective");

    glWindowPos2i(5,25);
    Print("Ambient=%.2f  Diffuse=%.2f Specular=%.2f Emission=%.2f Shininess=%.2f",ambient,diffuse,specular,emission,shiny);

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
/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
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

    else if(ch == 'c' || ch =='C')
        showCarOnly = (showCarOnly+1)%2;
    
    else if (ch == 'i' || ch == 'I')
      light = 1-light;

    //  Change field of view angle
    
    else if (ch=='a' && ambient>0)
        ambient -= 5;
    else if (ch=='A' && ambient<100)
        ambient += 5;
    //  Diffuse level
    else if (ch=='d' && diffuse>0)
        diffuse -= 5;
    else if (ch=='D' && diffuse<100)
        diffuse += 5;
    //  Specular level
    else if (ch=='s' && specular>0)
        specular -= 5;
    else if (ch=='S' && specular<100)
        specular += 5;
    //  Emission level
    else if (ch=='e' && emission>0)
        emission -= 5;
    else if (ch=='E' && emission<100)
        emission += 5;
    //  Shininess level
    else if (ch=='n' && shininess>-1)
        shininess -= 1;
    else if (ch=='N' && shininess<7)
        shininess += 1;
    else if (ch == 'W' && light_x <=4.0)
        light_x += 0.1;
    else if (ch == 'w' && light_x > 0.0)
        light_x -= 0.1;
    else if (ch == 'L' && light_z <=8.0)
        light_z += 0.1;
    else if (ch == 'l' && light_z > 0.0)
        light_z -= 0.1;
    else if (ch == 'Y' && ylight <=100)
        ylight += 5;
    else if (ch == 'y' && ylight > -100)
        ylight -= 5;


    else if (ch == ' ')
        move = 1-move;
    else if (ch == '-' && ch>1)
        fov--;
    else if (ch == '+' && ch<179)
        fov++;
    
    shiny = shininess<0 ? 0 : pow(2.0,shininess);

    //  Reproject
    Project();
    glutIdleFunc(move?idle:NULL);
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(900, 900);

    glutCreateWindow("Assignment 3: Shanmukha Vamshi Kuruba");

    #ifdef USEGLEW
    if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
    #endif

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutSpecialFunc(special);

    glutKeyboardFunc(key);

    glutIdleFunc(idle);

    texture[0] = LoadTexBMP("textures/asphalt_texture.bmp");
    texture[1] = LoadTexBMP("textures/grass_512_24bpp.bmp");
    texture[2] = LoadTexBMP("textures/marking_512_24bpp.bmp");
    texture[3] = LoadTexBMP("textures/rolex_logo.bmp");
    texture[4] = LoadTexBMP("textures/metal_pole_rusty_03.bmp");
    texture[5] = LoadTexBMP("textures/OldIron01_512_24bpp.bmp");
    texture[6] = LoadTexBMP("textures/glass.bmp");
    texture[7] = LoadTexBMP("textures/carbon_fiber.bmp");
    texture[8] = LoadTexBMP("textures/tire.bmp");
    texture[9] = LoadTexBMP("textures/tire_rim.bmp");
    texture[10] = LoadTexBMP("textures/ferrari_nose_texture.bmp");
    texture[11] = LoadTexBMP("textures/glossy_ferrari_red_512x512.bmp");
    texture[12] = LoadTexBMP("textures/sponsor_stripe_512x256.bmp");


    glutMainLoop();

    return 1;
}