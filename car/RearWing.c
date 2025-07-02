#include "Utils.h"
#include "CarParts.h"

void Wing_Holder(char side)
{
    glPushMatrix();
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);


    glPushMatrix();

    // glRotated(30, 1,0,0);


    int samples = 50;
    float dy = 25 - 13;
    if(side == 'r')
    {
        glBegin(GL_QUAD_STRIP);
        for(int i =0;i<samples;i++)
        {
            float t = (float) i/ (float) samples;
            float x = -5*Sin(90 + 135 * t);
            
            glVertex3f(10+x, 12 + t*dy, 102 - (2+2*t));
            glVertex3f(11+x, 12 + t*dy, 102 + (2+2*t));
        }
        glEnd();
    }
    else
    {
        glBegin(GL_QUAD_STRIP);
        for(int i =0;i<samples;i++)
        {
            float t = (float) i/ (float) samples;
            float x = -5*Sin(90 + 135 * t);
            
            glVertex3f(-(10+x), 12 + t*dy, 102 - (2+2*t));
            glVertex3f(-(11+x), 12 + t*dy, 102 + (2+2*t));
        }
        glEnd();
    }
    
    glPopMatrix();
    glPopMatrix();
}


void RearWing()
{
    Wing_Holder('r');
    Wing_Holder('l');
}