#include "CSCI5229.h"
#include "objects.h"

void Plane(int type, 
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

void cube(double x,double y,double z,
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

void LightPole(double x,double y,double z,double r, double h, char side)
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

void LightPoles(double wall_w, double road_w, double road_l)
{
    for(int z = -road_l/2; z< road_l/2;z+=30)
    {
        LightPole(road_w/2+1,0,z, 0.25, wall_w*4, 'r');
        LightPole(-(road_w/2+1),0,z, 0.25, wall_w*4, 'l');
    }
}