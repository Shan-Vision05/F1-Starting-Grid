#include "CSCI5229.h"
#include "car.h"
#include "objects.h"

typedef struct { float z, y; } Vec2;
typedef struct { float x, y, z; } Vec3;

Vec2 Nose_CP_Top[7] = {
    {-5, 7},
    {8, 7},
    {12,6},
    {17,4},
    {20,1},
    {21,0},
    {20,0}    
};

Vec2 Nose_CP_Down[4] ={
    {-5,2},
    {9,2},
    {17,1},
    {20,0},
};



Vec2 GetPoint_Bezier(const Vec2 *CP, size_t n, float t){
    // make a local copy we can lerp in-place
    Vec2 tmp[n];
    for(size_t i=0; i<n; ++i)
        tmp[i] = CP[i];

    // de Casteljau: iteratively blend
    for(size_t k=1; k<n; ++k){
        for(size_t i=0; i<n-k; ++i){
            float u = 1 - t;
            tmp[i].z = u*tmp[i].z + t*tmp[i+1].z;
            tmp[i].y = u*tmp[i].y + t*tmp[i+1].y;
        }
    }
    // the first entry is the point on the curve
    return tmp[0];
}

void CarNose()
{
    glPushMatrix();
    glTranslated(0, 1, 0);
    int samples = 10;
    glColor3f(0.8, 0.1, 0.1);
    glBegin(GL_TRIANGLE_STRIP);

    //Top part of the Nose
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(Nose_CP_Top, 7, t);

        float nose_w = 4 - 3 * t; // tapering as it reaches the tip

        glVertex3f(  -nose_w, point.y, point.z);
        // right vertex
        glVertex3f(  nose_w, point.y, point.z);
    }
    glEnd();

    // Bottom Part of the nose
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(Nose_CP_Down, 4, t);

        float nose_w = 4 - 3 * t; // tapering as it reaches the tip

        glVertex3f(  -nose_w, point.y, point.z);
        // right vertex
        glVertex3f(  nose_w, point.y, point.z);
    }
    glEnd();

    //Left Side of the nose
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point1 = GetPoint_Bezier(Nose_CP_Down, 4, t);
        Vec2 point2 = GetPoint_Bezier(Nose_CP_Top, 7, t);

        float nose_w = 4 - 3 * t; // tapering as it reaches the tip

        glVertex3f(  nose_w, point1.y, point1.z);
        glVertex3f(  nose_w, point2.y, point2.z);
        // right vertex
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point1 = GetPoint_Bezier(Nose_CP_Down, 4, t);
        Vec2 point2 = GetPoint_Bezier(Nose_CP_Top, 7, t);

        float nose_w = 4 - 3 * t; // tapering as it reaches the tip

        glVertex3f(  -nose_w, point1.y, point1.z);
        glVertex3f(  -nose_w, point2.y, point2.z);
        // right vertex
    }

    glEnd();

    
    glPopMatrix();
}

void WheelStrip(double x, double y, double z, double h, double ro)
{
    //left
        //  Save transformation
    glPushMatrix();
    //  Offset and scale

    glTranslated(x,y,z);
    glRotated(ro, 0,0,1);
    glScaled(1.0,1.0,1.0);

    glColor3f(0.7,0.7,0.7);
    glBegin(GL_QUAD_STRIP);
    for (int th=0;th<=360;th+=10)
    {
            glVertex3d(h/2, Cos(th),Sin(th));
            glVertex3d(-h/2, Cos(th), Sin(th));
    }
    glEnd();
    

    //  Undo transformations
    glPopMatrix();
}

void wheels()
{

    WheelStrip(0,1.0, 0, 1, 0);

}



void car()
{
    // wheels();
    CarNose();

}
