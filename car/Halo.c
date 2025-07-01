#include "Utils.h"
#include "CarParts.h"
#include<math.h>

Vec2 Back_Tube_CP_L[3] ={
    {-10,0},
    {-10,-20},
    {0, -20}
};

Vec2 Back_Tube_CP_R[3] ={
    {10,0},
    {10,-20},
    {0, -20}
};

Vec2 Front_Tube_CP[3] ={
    {0, -30},
    {10, -23},
    {10, -17.32}
};

inline float dot(const Vec3 a, const Vec3 b) {
    return a.ax1 * b.ax1
         + a.ax2 * b.ax2
         + a.ax3 * b.ax3;
}

void HaloTube(char side)
{

    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);


    glPushMatrix();

    glRotated(30, 1,0,0);


    int samples = 50;
    glBegin(GL_QUAD_STRIP);
    for(int i =0;i<samples;i++)
    {
        float t = (float) i/ (float) samples;
        float t_1 = (float) (i+1) / (float) samples;
        Vec2 point1 = GetPoint_Bezier(Back_Tube_CP_L,3, t);
        Vec2 point2 = GetPoint_Bezier(Back_Tube_CP_L,3,t_1);

        Vec2 d1 = GetTangent_Bezier(Back_Tube_CP_L,3,t);
        Vec2 d2 = GetTangent_Bezier(Back_Tube_CP_L,3,t_1);

        if (side == 'r')
        {
            point1 = GetPoint_Bezier(Back_Tube_CP_R,3, t);
            point2 = GetPoint_Bezier(Back_Tube_CP_R,3,t_1);

            d1 = GetTangent_Bezier(Back_Tube_CP_R,3,t);
            d2 = GetTangent_Bezier(Back_Tube_CP_R,3,t_1);
        }

        

        Vec3 T1 = Normalize((Vec3){d1.ax1, 0, d1.ax2});
        Vec3 T2 = Normalize((Vec3){d2.ax1, 0, d2.ax2});

        Vec3 up = {0,1,0};
        // if (fabs(dot(up,T1)) > 0.9f) up = (Vec3){1,0,0};

        Vec3 N1 = Normalize(cross(up, T1));
        Vec3 N2 = Normalize(cross(up, T2));

        Vec3 BN1 = Normalize(cross(N1, T1));
        Vec3 BN2 = Normalize(cross(N2, T2));


        for (int th=0;th<=360;th+=5)
        {
            // glNormal3f(Cos(th),0,Sin(th));

            // float s = th / 360.0; 
            // top
            // glTexCoord2f(s, 1.0);
            Vec3 Offset_1 = {
                N1.ax1 * Cos(th)* (1+t) + BN1.ax1 * Sin(th),
                N1.ax2 * Cos(th)* (1+t) + BN1.ax2 * Sin(th),
                N1.ax3 * Cos(th)* (1+t) + BN1.ax3 * Sin(th),
            };
            glNormal3f(Offset_1.ax1, Offset_1.ax2, Offset_1.ax3);
            glVertex3f(point1.ax1 + Offset_1.ax1, Offset_1.ax2 , point1.ax2 + Offset_1.ax3);
            // bottom
            // glTexCoord2f(s, 0.0);
            Vec3 Offset_2 = {
                N2.ax1 * Cos(th)* (1+t_1)+ BN2.ax1 * Sin(th),
                N2.ax2 * Cos(th)* (1+t_1)+ BN2.ax2 * Sin(th),
                N2.ax3 * Cos(th)* (1+t_1)+ BN2.ax3 * Sin(th),
            };
            glNormal3f(Offset_2.ax1, Offset_2.ax2, Offset_2.ax3);
            glVertex3f(point2.ax1 +Offset_2.ax1, Offset_2.ax2, point2.ax2+Offset_2.ax3);  
        }
    }
    
    glEnd();
    // glDisable(GL_TEXTURE_2D);
    

    glPopMatrix();
}


void HaloFront()
{
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);


    glPushMatrix();

    // glRotated(30, 1,0,0);


    int samples = 200;
    glBegin(GL_QUAD_STRIP);
    for(int i =0;i<samples;i++)
    {
        float t = (float) i/ (float) samples;
        float t_1 = (float) (i+1) / (float) samples;
        // printf("%f", t);
        Vec2 point1 = GetPoint_Bezier(Front_Tube_CP,3, t);
        Vec2 point2 = GetPoint_Bezier(Front_Tube_CP,3,t_1);

        Vec2 d1 = GetTangent_Bezier(Front_Tube_CP,3,t);
        Vec2 d2 = GetTangent_Bezier(Front_Tube_CP,3,t_1);

        Vec3 T1 = Normalize((Vec3){0, d1.ax1, d1.ax2});
        Vec3 T2 = Normalize((Vec3){0, d2.ax1, d2.ax2});

        Vec3 side = {1,0,0};
        // if (fabs(dot(up,T1)) > 0.9f) up = (Vec3){1,0,0};

        Vec3 N1 = Normalize(cross(side, T1));
        Vec3 N2 = Normalize(cross(side, T2));

        Vec3 BN1 = cross(N1, T1);
        Vec3 BN2 = cross(N2, T2);


        for (int th=0;th<=360;th+=5)
        {
            // glNormal3f(Cos(th),0,Sin(th));

            // float s = th / 360.0; 
            // top
            // glTexCoord2f(s, 1.0);
            Vec3 Offset_1 = {
                N1.ax1 * Cos(th) + BN1.ax1 * Sin(th) * (1+2*t),
                N1.ax2 * Cos(th) + BN1.ax2 * Sin(th) * (1+2*t),
                N1.ax3 * Cos(th) + BN1.ax3 * Sin(th) * (1+2*t),
            };
            glNormal3f(Offset_1.ax1, Offset_1.ax2, Offset_1.ax3);
            glVertex3f( Offset_1.ax1, point1.ax1 +Offset_1.ax2 , point1.ax2 + Offset_1.ax3);
            // bottom
            // glTexCoord2f(s, 0.0);
            Vec3 Offset_2 = {
                N2.ax1 * Cos(th)+ BN2.ax1 * Sin(th) * (1+2*t_1),
                N2.ax2 * Cos(th)+ BN2.ax2 * Sin(th) * (1+2*t_1),
                N2.ax3 * Cos(th)+ BN2.ax3 * Sin(th) * (1+2*t_1),
            };
            glNormal3f(Offset_2.ax1, Offset_2.ax2, Offset_2.ax3);
            glVertex3f(Offset_2.ax1, point2.ax1 +Offset_2.ax2, point2.ax2+Offset_2.ax3);  
        }

    }
    
    glEnd();
    // glDisable(GL_TEXTURE_2D);
    

    glPopMatrix();
}
void Halo()
{
    glPushMatrix();
    glTranslated(0,19,65);
    glScaled(0.7,0.5,0.7);
    glColor3f(0.3,0.3,0.3);
        HaloTube('l');
        HaloTube('r');
        HaloFront();
    glPopMatrix();
}