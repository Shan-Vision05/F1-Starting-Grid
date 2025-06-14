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

void PlaneNoColor(int type, 
    double x, double y, double z,
    double th, double pi, double ro,
    double h, double w)
{
    glPushMatrix();

    glTranslated(x, y, z);
    glRotated(pi, 1, 0, 0);
    glRotated(th, 0, 1, 0);
    glRotated(ro, 0, 0, 1);

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
// glColor3f(1,0,0);
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

    glColor3f(1,0,0);
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

void GridPosMarker(double z, double h, double w)
{
    glPushMatrix();
   //  Offset and scale
   glTranslated(0,0,z);
    int thickness = 1;
    int length = 15;
    double adjGridOffset = 7.5;

    glColor3f(0.8,0.8,0.8);
    PlaneNoColor(GL_POLYGON, -w/5,0,adjGridOffset, 0, 0, 0,  thickness, length );

    PlaneNoColor(GL_POLYGON, -w/5 - length/2,0,length/4+adjGridOffset, 0,0,0,  length/2, thickness);

    PlaneNoColor(GL_POLYGON, -w/5 + length/2,0,length/4+adjGridOffset, 0,0,0,  length/2, thickness);

    glColor3f(0.7,0.7,0);
    PlaneNoColor(GL_POLYGON, -w/5 + 2*length/3,0,adjGridOffset+2, 0, 0, 0,  thickness, length );

    glColor3f(0.8,0.8,0.8);
    PlaneNoColor(GL_POLYGON, w/5,0,-adjGridOffset, 0, 0, 0, thickness, length );

    PlaneNoColor(GL_POLYGON, w/5 - length/2,0,length/4-adjGridOffset, 0,0,0,  length/2, thickness);

    PlaneNoColor(GL_POLYGON, w/5 + length/2,0,length/4-adjGridOffset, 0,0,0,  length/2, thickness);

    glColor3f(0.7,0.7,0);
    PlaneNoColor(GL_POLYGON, w/5 + 2*length/3,0,-adjGridOffset+2, 0, 0, 0, thickness, length );

    glPopMatrix();
}

void GridPosMarkers(double h, double w)
{
    double z = h/2.5;
    int count = 0;
    while (count < 10)
    {
        GridPosMarker(z, h, w);
        z-=30.0;
        count+=2;
    }
}


void GrandStand(double h, double w, double side_walk_w)
{   int width = 2;
    int height = 1;
    int length = h;

    //Right Grand Stand
    for(int i = 1; i< 10;i++)
    {
        if (i%2 == 0)
            glColor3f(0.5,0.5,0.5);
        else
            glColor3f(0.6,0.6,0.6);
        
        cube(w/2+side_walk_w+ (2*(i-1)+1)*width, i*height, 0, width, i*height, length/2,0 );
    }

    //Left Grand Stand
    for(int i = 1; i<10;i++)
    {
        if (i%2 == 0)
            glColor3f(0.5,0.5,0.5);
        else
            glColor3f(0.6,0.6,0.6);
        
        cube(-w/2-side_walk_w- (2*(i-1)+1)*width, i*height, 0, width, -i*height, length/2,0 );
    }

}

