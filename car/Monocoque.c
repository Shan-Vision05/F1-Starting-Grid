#include "Utils.h"
#include "CarParts.h"


Vec2 Mono_Front_T[4] ={
    {44,20},
    {58, 19},
    {72, 18},
    {96, 16}
};

Vec2 Mono_Front_B[5] ={
    {44, 12},
    {46, 10},
    {58, 9},
    {72, 8},
    {96, 10}

};

void Monocoque_Front()
{
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);


    glPushMatrix();
    // glTranslated(0, 1, 0);
    int samples = 10;
    glColor3f(0.5, 0.0, 0.0);

    int angle = 180;
    int amp = 5;
    

    glBegin(GL_TRIANGLE_STRIP);
    //Top part of the Nose
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(Mono_Front_T, 4, t);

        float nose_w = 4.4 + amp * Sin(angle*t); // tapering as it reaches the end

        Vec2 d = GetTangent_Bezier(Mono_Front_T, 4, t);
        Vec3 T = {0.0, d.ax2, d.ax1};
        Vec3 W = {1.0, 0.0, 0.0};
        Vec3 N = cross(T,W);

        
        glNormal3f(N.ax1, N.ax2, N.ax3);

        glVertex3f(  -nose_w, point.ax2, point.ax1);
        glVertex3f(  nose_w, point.ax2, point.ax1);
    }
    glEnd();

    // Bottom Part of the nose
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(Mono_Front_B, 5, t);

        float nose_w = 4.4 + amp * Sin(angle*t); // tapering as it reaches the end

        Vec2 d = GetTangent_Bezier(Mono_Front_B, 5, t);
        Vec3 T = {0.0, d.ax2, d.ax1};
        Vec3 W = {1.0, 0.0, 0.0};
        Vec3 N = cross(W, T);

        
        glNormal3f(N.ax1, N.ax2, N.ax3);

        glVertex3f(  -nose_w, point.ax2, point.ax1);
        glVertex3f(  nose_w, point.ax2, point.ax1);
    }
    glEnd();

    // //Left Side of the nose
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point1 = GetPoint_Bezier(Mono_Front_B, 5, t);
        Vec2 point2 = GetPoint_Bezier(Mono_Front_T, 4, t);

        float nose_w = 4.4 + amp * Sin(angle*t); // tapering as it reaches the end
        float dx = amp * angle * (3.14159/180) * Cos(angle*t);

        Vec2 d = GetTangent_Bezier(Mono_Front_T, 4, t);

        Vec3 T = {dx, d.ax2, d.ax1};
        Vec3 W = {0.0, point1.ax2 - point2.ax2, point1.ax1 - point2.ax1};
        Vec3 N = cross(T,W);

        glNormal3f(N.ax1, N.ax2, N.ax3);

        glVertex3f(  nose_w, point1.ax2, point1.ax1);
        glVertex3f(  nose_w, point2.ax2, point2.ax1);
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point1 = GetPoint_Bezier(Mono_Front_B, 5, t);
        Vec2 point2 = GetPoint_Bezier(Mono_Front_T, 4, t);
        float nose_w = 4.4 + amp * Sin(angle*t); // tapering as it reaches the end
        float dx = amp * angle * (3.14159/180) * Cos(angle*t);

        Vec2 d = GetTangent_Bezier(Mono_Front_T, 4, t);

        Vec3 T = {-dx, d.ax2, d.ax1};
        Vec3 W = {0.0, point1.ax2 - point2.ax2, point1.ax1 - point2.ax1};
        Vec3 N = cross(W,T);

        glNormal3f(N.ax1, N.ax2, N.ax3);

        glVertex3f(  -nose_w, point1.ax2, point1.ax1);
        glVertex3f(  -nose_w, point2.ax2, point2.ax1);
    }

    glEnd();

    glColor3f(1, 1, 1);

    glPopMatrix();
}