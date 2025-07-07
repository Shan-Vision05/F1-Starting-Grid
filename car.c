#include "CSCI5229.h"
#include "car.h"
#include "objects.h"

#include "car/CarParts.h"
#include "car/Utils.h"


void WheelRod(double x, double y, double z, double phi, double theta, double ro, double h, unsigned int text_cf)
{

    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();
    float r = 0.5;
    glTranslated(x,y,z);
    glRotated(phi, 1,0,0);
    glRotated(theta, 0,1,0);
    glRotated(ro, 0,0,1);
    glScaled(r,1.0,r);
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, text_cf);

    
    glBegin(GL_QUAD_STRIP);
    for (int th=0;th<=360;th+=30)
    {       
        float s = th / 360.0; 
        glNormal3f(Cos(th),0,Sin(th));
        glTexCoord2f(s, 1.0);
        glVertex3d(Cos(th),0,Sin(th));
        glTexCoord2f(s, 0.0);
        glVertex3d(Cos(th),h,Sin(th));
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    

    glPopMatrix();
}

void WheelStrip(double x, double y, double z, double h, double r, unsigned int tex_wheel, unsigned int text_rim)
{
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();

    glTranslated(x,y,z);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex_wheel);

    glColor3f(1,1,1);
    glBegin(GL_QUAD_STRIP);
    for (int th=0;th<=360;th+=10)
    {
        float s = th / 360.0f;
        glNormal3f(0, r*Cos(th),r*Sin(th));

        glTexCoord2f(s, 1.0);
        glVertex3d(h/2, r*Cos(th),r*Sin(th));

        glTexCoord2f(s, 0.0);
        glVertex3d(-h/2, r*Cos(th), r*Sin(th));
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, text_rim);

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(1,0,0);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(h/2, 0.0, 0.0);

    
    for (int th=0;th<=360;th+=10)
    {
        glNormal3f(1,0,0);
        glTexCoord2f((Cos(th) +1)*0.5, (Sin(th)+1)*0.5);
        glVertex3d(h/2, r*Cos(th),r*Sin(th));
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, text_rim);

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(1,0,0);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(-h/2, 0.0, 0.0);
    
    for (int th=0;th<=360;th+=10)
    {
        glNormal3f(-1,0,0);
        glTexCoord2f((Cos(th) +1)*0.5, (Sin(th)+1)*0.5);
        glVertex3d(-h/2, r*Cos(th),r*Sin(th));
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    

    glPopMatrix();
}

void wheels(unsigned int tex_wheel, unsigned int text_rim, unsigned int text_cf)
{
    WheelRod(10,4,9, 0,0,90, 20, text_cf);
    WheelRod(10, 4, -38, 0,0,90, 20, text_cf);
    
    WheelStrip(12,4,9, 8, 5, tex_wheel, text_rim);
    WheelStrip(-12,4,9, 8, 5, tex_wheel, text_rim);

    WheelStrip(12,4,-38, 8, 5, tex_wheel, text_rim);
    WheelStrip(-12,4,-38, 8, 5, tex_wheel, text_rim);
}


void NewCar(unsigned int tex_end, unsigned int tex_wheel, unsigned int tex_rim, unsigned int tex_nose,
    unsigned int tex_nose_side, unsigned int text_side_strip)
    {
        glPushMatrix();

        glScaled(0.5, 0.5, 0.5);
        glPushMatrix();

        glTranslated(0,-5,-58);
        glScaled(0.7,0.7,0.7);

        // registerPickableBox(
        //     (Vec3){0,10,44},
        //     (Vec3) {30, 30, 3},
        //     100.0,
        //     2, 
        //     Garage_Vertice,
        //     garage_vert_siz
        // );

        

        Wing(tex_end, tex_nose, tex_nose_side);
        Monocoque_Front(tex_end, text_side_strip, tex_nose_side);
        Halo(tex_end);
        RearWing(tex_end);
        
        glPopMatrix();

        // glDisable(GL_LIGHTING);
        // glColor3f(1,0,0);
        // glPushMatrix();
        // // 
        // // glTranslatef(-9.918589f, 13.582701f, -223.756729f);
        // // glutWireSphere(5.0,12,12);
        // glPopMatrix();

        
        glEnable(GL_LIGHTING);

        glTranslated(0,0,2);
        wheels(tex_wheel, tex_rim, tex_end);
        glPopMatrix();
        
    }
