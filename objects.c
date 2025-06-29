#include "CSCI5229.h"
#include "objects.h"

void Plane(int type, 
    double x, double y, double z,
    double th, double pi, double ro,
    double r, double g, double b,
    double h, double w, unsigned int texture, double stretch_x, double stretch_y, int flip)
{
    
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();
    glColor3f(r, g, b);
    glTranslated(x, y, z);
    glRotated(pi, 1, 0, 0);
    glRotated(th, 0, 1, 0);
    glRotated(ro, 0, 0, 1);

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D,texture);

    glBegin(type);
    
    if (flip==1)
    {
        glNormal3f(0,1,0);
        glTexCoord2f(0,0); glVertex3f(-w/2,0,h/2);
        glTexCoord2f(stretch_x,0); glVertex3f(w/2,0,h/2);
        glTexCoord2f(stretch_x,stretch_y); glVertex3f(w/2, 0, -h/2);
        glTexCoord2f(0,stretch_y); glVertex3f(-w/2,0,-h/2);
    }
    else
    {
        glNormal3f(0,-1,0);
        glTexCoord2f(0,stretch_y); glVertex3f(-w/2,0,h/2);
        glTexCoord2f(stretch_x,stretch_y); glVertex3f(w/2,0,h/2);
        glTexCoord2f(stretch_x,0); glVertex3f(w/2, 0, -h/2);
        glTexCoord2f(0,0); glVertex3f(-w/2,0,-h/2);
    }
    
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

}


void Arc(double x, double y, double z, double innerR, double outerR, double start_ang, double end_ang, unsigned int texture)
{
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);


    glPushMatrix();
    glTranslated(x, y, z);
    glColor3f(0.5, 0.5, 0.5);

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D,texture);

    glBegin(GL_QUAD_STRIP);
    int steps = 50;
    for(int i=0; i<= steps; i++)
    {
        float t = (float) i/(float)steps;

        float angle = start_ang + t*(end_ang - start_ang);

        float xOuter = Cos(angle)*outerR;
        float yOuter = Sin(angle)*outerR;
        // point on inner circle
        float xInner = Cos(angle)*innerR;
        float yInner = Sin(angle)*innerR;
        // order matters: inner, then outer (or vice versa) for a strip
        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(t, 0.0);
        glVertex3f(xInner,0, yInner);
        glTexCoord2f(t, 1.0);
        glVertex3f(xOuter,0, yOuter);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void PlaneNoColor(int type, 
    double x, double y, double z,
    double th, double pi, double ro,
    double h, double w, unsigned int texture)
{
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();

    glTranslated(x, y, z);
    glRotated(pi, 1, 0, 0);
    glRotated(th, 0, 1, 0);
    glRotated(ro, 0, 0, 1);

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D,texture);

    glBegin(type);
    glNormal3f(0,1,0);
    glTexCoord2f(0,1); glVertex3f(-w/2,0,h/2);
    glTexCoord2f(1,1); glVertex3f(w/2,0,h/2);
    glTexCoord2f(1,0); glVertex3f(w/2, 0, -h/2);
    glTexCoord2f(0,0); glVertex3f(-w/2,0,-h/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}


/*
 *
 *  Note: This function is inspired from the example file provided in class.
 *
 */

void cube(double x,double y,double z,
    double dx,double dy,double dz,
    double th, unsigned int texture)
{

float white[] = {1,1,1,1};
float black[] = {0,0,0,1};
glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

//  Save transformation
glPushMatrix();
//  Offset
glTranslated(x,y,z);
glRotated(th,0,0,1);
glScaled(dx,dy,dz);



glEnable(GL_TEXTURE_2D);
glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
// glColor3f(1,1,1);
glBindTexture(GL_TEXTURE_2D,texture);


//  Cube
glBegin(GL_QUADS);
//  Front
// glColor3f(1,0,0);
glNormal3f(0,0,1);
glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
//  Back
glNormal3f(0,0,-1);
glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
//  Right
glNormal3f(1,0,0);
glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
//  Left
glNormal3f(-1,0,0);
glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
//  Topfrom image
glNormal3f(0,1,0);
glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
//  Bottom
glNormal3f(0,-1,0);
glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
//  End
glEnd();

glDisable(GL_TEXTURE_2D);
//  Undo transformations
glPopMatrix();
}

void cubeWLight(double x,double y,double z,
    double dx,double dy,double dz,
    double th, unsigned int texture_lamp)
{
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    float emCol[] = { 1.0, 1.0, 1.0, 1.0 };
    // No emission
    float noEm[] = { 0,0,0,1 };
    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x,y,z);
    glRotated(th,0,0,1);
    glScaled(dx,dy,dz);
    //  Cube



    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
       glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,texture_lamp);

    glBegin(GL_QUADS);
    //  Front
    // glColor3f(1,0,0);
    glNormal3f(0,0,1);
    glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
    glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
    glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
    glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
    //  Back
    
    glNormal3f(0,0,-1);
    glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
    
    //  Right
    glNormal3f(1,0,0);
    glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
    //  Left
    
    //  Topfrom image
    glNormal3f(0,1,0);
    glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
    //  Bottom
    
    glNormal3f(0,-1,0);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,emCol);
    glNormal3f(-1,0,0);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,noEm);
    glEnd();
    
    glPopMatrix();
}

void LightPole(double x,double y,double z,double r, double h, char side, unsigned int texture_pole, unsigned int texture_lamp)
{

    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);


   glPushMatrix();
   glTranslated(x,y,z);
   glScaled(r,1.0,r);

   glColor3f(1, 1, 1);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_pole);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBegin(GL_QUAD_STRIP);
    for (int th = 0; th <= 360; th += 30) {
        float s = th / 360.0;

        glNormal3f(Cos(th), 0, Sin(th));

        // top
        glTexCoord2f(s, 1.0);
        glVertex3d(Cos(th), h,   Sin(th));
        // bottom
        glTexCoord2f(s, 0.0);
        glVertex3d(Cos(th), 0.0, Sin(th));
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    int head_size = h/4;
    int head_angle = 70;

    int x_offset = -Sin(head_angle)*head_size/2 + 0.25;
    int y_offset = h + Cos(head_angle)*head_size/2;

    glColor3f(1,1,1);
    if (side == 'r')
        cubeWLight(x_offset+x, y_offset+y,z, 0.25,head_size/2,head_size/4,70, texture_lamp);
    else
        cubeWLight(-x_offset+x, y_offset,z, 0.25,head_size/2,head_size/4,110, texture_lamp);
}

void LightPoles(double wall_w, double road_w, double road_l, unsigned int texture_pole, unsigned int texture_lamp)
{
    for(int z = -road_l/2; z< road_l/2;z+=70)
    {
        LightPole(road_w/2+1,0,z, 0.25, wall_w*4, 'r', texture_pole, texture_lamp);
        LightPole(-(road_w/2+1),0,z, 0.25, wall_w*4, 'l', texture_pole, texture_lamp);
    }
}

void GridPosMarker(double z, double h, double w, unsigned int texture)
{
    glPushMatrix();
   //  Offset and scale
   glTranslated(0,0,z);
    int thickness = 1;
    int length = 15;
    double adjGridOffset = 7.5;

    glColor3f(0.8,0.8,0.8);
    PlaneNoColor(GL_POLYGON, -w/5,0,adjGridOffset, 0, 0, 0,  thickness, length, texture);

    PlaneNoColor(GL_POLYGON, -w/5 - length/2,0,length/4+adjGridOffset, 0,0,0,  length/2, thickness, texture);

    PlaneNoColor(GL_POLYGON, -w/5 + length/2,0,length/4+adjGridOffset, 0,0,0,  length/2, thickness, texture);

    glColor3f(0.7,0.7,0);
    PlaneNoColor(GL_POLYGON, -w/5 + 2*length/3,0,adjGridOffset+2, 0, 0, 0,  thickness, length , texture);

    glColor3f(0.8,0.8,0.8);
    PlaneNoColor(GL_POLYGON, w/5,0,-adjGridOffset, 0, 0, 0, thickness, length, texture );

    PlaneNoColor(GL_POLYGON, w/5 - length/2,0,length/4-adjGridOffset, 0,0,0,  length/2, thickness, texture);

    PlaneNoColor(GL_POLYGON, w/5 + length/2,0,length/4-adjGridOffset, 0,0,0,  length/2, thickness, texture);

    glColor3f(0.7,0.7,0);
    PlaneNoColor(GL_POLYGON, w/5 + 2*length/3,0,-adjGridOffset+2, 0, 0, 0, thickness, length , texture);

    glPopMatrix();
}

void GridPosMarkers(double x, double y, double z, double h, double w, unsigned int texture)
{
    glPushMatrix();
    glTranslated(x,y,z);
    double z_val = h/1.2;
    int count = 0;
    while (count < 20)
    {
        GridPosMarker(z_val, h, w, texture);
        z_val-=30.0;
        count+=2;
    }
    glPopMatrix();
}

void cylinder(double x, double y, double z, double h, double ro, unsigned int texture)
{

    
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);


    glPushMatrix();

    glTranslated(x,y,z);
    glRotated(ro, 0,0,1);
    glScaled(0.25,1.0,0.25);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBegin(GL_QUAD_STRIP);
    for (int th=0;th<=360;th+=30)
    {
        glNormal3f(Cos(th),0,Sin(th));

        float s = th / 360.0; 
        // top
        glTexCoord2f(s, 1.0);
        glVertex3d(Cos(th), h,   Sin(th));
        // bottom
        glTexCoord2f(s, 0.0);
        glVertex3d(Cos(th), 0.0, Sin(th));
}
    glEnd();
    glDisable(GL_TEXTURE_2D);
    

    glPopMatrix();
}

void GrandStandPoles(double w, double side_walk_w, double stand_seat_w, int i, double z_offset, unsigned int texture)
{
    
    cylinder(-w/2-side_walk_w- (2*(i-2)+1)*stand_seat_w,0,z_offset, 40,0, texture);
    cylinder(-w/2-side_walk_w- (2*(i/2-1)+1)*stand_seat_w,0,z_offset, 40,0, texture);
    cylinder(-w/2-side_walk_w- stand_seat_w,0,z_offset, 40,0, texture);
}

void GrandStand(double h, double w, double side_walk_w, unsigned int tex_pole, unsigned int tex_seating, unsigned int text_roof, double offset)
{   int width = 2;
    int height = 1;
    int length = h;
    int i =0;

    glColor3f(0.2,0.2,0.2);
    //Right Grand Stand
    for(i = 1; i< 10;i++)
    {        
        cube(w/2+side_walk_w+ (2*(i-1)+1)*width + offset, i*height, 0, width, i*height, length/2,0 , tex_seating);
    }

    //Left Grand Stand
    for(i = 1; i<10;i++)
    {
        cube(-w/2-side_walk_w- (2*(i-1)+1)*width, i*height, 0, width, -i*height, length/2,0 , tex_seating);
    }

    // glColor3f(0.6,0.6,0.6);
    GrandStandPoles(w, side_walk_w, width, i, 0, tex_pole);
    GrandStandPoles(w, side_walk_w, width, i, -h/2+5, tex_pole);
    GrandStandPoles(w, side_walk_w, width, i, h/2-5, tex_pole);

    // Roof
    int x =-w/2-side_walk_w- i*width;
    int z = 0;
    int y = 40;

    int roof_width = i*width;
    int roof_len = h/2;
    int y_offset = Cos(45)*roof_width/2;
    int x_offset = Sin(45)*roof_width/2;

    cube(x,y,z, roof_width, 0.5, roof_len, 0, text_roof);
    cube(x+roof_width+x_offset/2,y -y_offset/2-0.5,z, roof_width/4, 0.5, roof_len, -45, text_roof);

}


void circle(double x, double y, double z, double r, unsigned int texture)
{
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();
    //  Offset and scale
    glTranslated(x,y,z);
    glScaled(r,r,1.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glColor3f(0.5, 0, 0);

    //    int ph = 0;

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0,0,1);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0.0, 0.0, z);
    for (int th=0;th<=360;th+=10)
    {   
        glNormal3f(0,0, 1);
        glTexCoord2f((Cos(th) +1)*0.2, (Sin(th)+1)*0.2);
        glVertex3d(Cos(th),Sin(th),z);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
    

    glPopMatrix();
}

void StartLight(double w, double h, double x_offset, unsigned int texture, unsigned int tex_light)
{
    glColor3f(0.1, 0.1, 0.1);
    circle(x_offset,w/5-0,-h/4+0.5,0.75, tex_light);
    circle(x_offset,w/5-2,-h/4+0.5,0.75, tex_light);
    glColor3f(0.9, 0.0, 0.0);
    circle(x_offset,w/5-4,-h/4+0.5,0.75, tex_light);
    circle(x_offset,w/5-6,-h/4+0.5,0.75, tex_light);

    glEnable(GL_POLYGON_OFFSET_FILL);
    
    glPolygonOffset(1,1);
    glColor3f(0.4, 0.4, 0.4);
    cube(x_offset,w/5-3, -h/2+0.5, 1,4,0.5, 0, texture);
    glDisable(GL_POLYGON_OFFSET_FILL);
}


void StartLights(double h, double w, unsigned int texture, unsigned int tex_light)                                                         
{   
    glColor3f(0.4, 0.4, 0.4);
    cylinder(-w/2,0, -h/2, w/5, 0, texture);  
    cylinder(w/2,0, -h/2, w/5, 0, texture);


    cylinder(w/2,w/5, -h/2, w, 90, texture);
    cylinder(w/2,w/6, -h/2, w, 90, texture);


    //Ligths
    StartLight(w,h,0, texture, tex_light);
    StartLight(w,h,3, texture, tex_light);
    StartLight(w,h,-3, texture, tex_light);
    StartLight(w,h,6, texture, tex_light);
    StartLight(w,h,-6, texture, tex_light);
}


void Garage(double x, double y, double z, double s, unsigned int texture)
{
    double wall_width = 0.05 * s;
    glPushMatrix();
    glTranslated(x,y,z);

    cube(s,s/2, -s/2 -wall_width/2, s, s/2, wall_width, 0, texture);
    cube(s,s/2, +s/2 +wall_width/2, s, s/2, wall_width, 0, texture);

    cube(s, s-wall_width, 0, s, wall_width, s/2, 0, texture);

    cube(2*s - wall_width,s/2,0, wall_width, s/2, s/2, 0, texture);
    // Plane(GL_POLYGON, s, 0,s/2, 0, 0, 0,  )
    Plane(GL_POLYGON, s, 0,0, 0, 0,0, 1, 1, 1, s, 2*s, texture, 10, 20, 1);

    glPopMatrix();
}

void Garages(double x, double y, double z, double s, unsigned int texture)
{
    double wall_width = 0.05 * s;
    double offset =  s + 2*wall_width;

    glPushMatrix();
    glTranslated(x, y, z);
    for(int i= -9;i <=10;i++)
        Garage(0,0,i*offset, s, texture);
    glPopMatrix();

}
