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

Vec2 Monocoque_CP_Top[6] ={
    {-5,7},
    {-12,7},
    {-17,5},
    {-26,3},
    // {-35,1},
    // {-34,0.5}
    {-34, 2},
    {-34, 0.5}
};

Vec2 Monocoque_CP_Down[5] ={
    {-5,2},
    {-8,0},
    {-15,0},
    {-30,0},
    {-34,0.5}
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

    glColor3f(0.6, 0.1, 0.1);
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


void CarMonocoque()
{
    glPushMatrix();
    glTranslated(0, 1, 0);
    int samples = 10;
    glColor3f(0.8, 0.1, 0.1);

    int angle = 220;
    int amp = 5;

    glBegin(GL_TRIANGLE_STRIP);
    //Top part of the Nose
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(Monocoque_CP_Top, 6, t);

        float nose_w = 4 + amp * Sin(angle*t); // tapering as it reaches the tip

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
        Vec2 point = GetPoint_Bezier(Monocoque_CP_Down, 5, t);

        float nose_w = 4 + amp * Sin(angle*t); // tapering as it reaches the tip

        glVertex3f(  -nose_w, point.y, point.z);
        // right vertex
        glVertex3f(  nose_w, point.y, point.z);
    }
    glEnd();

    glColor3f(0.6, 0.1, 0.1);
    //Left Side of the nose
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point1 = GetPoint_Bezier(Monocoque_CP_Down, 5, t);
        Vec2 point2 = GetPoint_Bezier(Monocoque_CP_Top, 6, t);

        float nose_w = 4 + amp * Sin(angle*t); // tapering as it reaches the tip

        glVertex3f(  nose_w, point1.y, point1.z);
        glVertex3f(  nose_w, point2.y, point2.z);
        // right vertex
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point1 = GetPoint_Bezier(Monocoque_CP_Down, 5, t);
        Vec2 point2 = GetPoint_Bezier(Monocoque_CP_Top, 6, t);

        float nose_w = 4 + amp * Sin(angle*t); // tapering as it reaches the tip

        glVertex3f(  -nose_w, point1.y, point1.z);
        glVertex3f(  -nose_w, point2.y, point2.z);
        // right vertex
    }

    glEnd();

    glColor3f(0.6, 0.1, 0.1);
    cube(0,2,-35, 2, 1.5, 4, 0);

    
    glPopMatrix();
}

void WheelRod(double x, double y, double z, double phi, double theta, double ro, double h)
{
    //left
    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    float r = 0.5;
    glTranslated(x,y,z);
    glRotated(phi, 1,0,0);
    glRotated(theta, 0,1,0);
    glRotated(ro, 0,0,1);
    glScaled(r,1.0,r);

    

    //    int ph = 0;

    glBegin(GL_QUAD_STRIP);
    for (int th=0;th<=360;th+=30)
    {
            glVertex3d(Cos(th),0,Sin(th));
            glVertex3d(Cos(th),h,Sin(th));
    }
    glEnd();
    

    //  Undo transformations
    glPopMatrix();
}

void WheelStrip(double x, double y, double z, double h, double r)
{
    //left
        //  Save transformation
    glPushMatrix();
    //  Offset and scale

    glTranslated(x,y,z);
    // glRotated(ro, 0,0,1);
    // glScaled(1.0,r,r);

    glColor3f(0.3,0.3,0.3);
    glBegin(GL_QUAD_STRIP);
    for (int th=0;th<=360;th+=10)
    {
            glVertex3d(h/2, r*Cos(th),r*Sin(th));
            glVertex3d(-h/2, r*Cos(th), r*Sin(th));
    }
    glEnd();

    glColor3f(0.2,0.2,0.2);
    glBegin(GL_TRIANGLE_FAN);
    for (int th=0;th<=360;th+=10)
    {
            glVertex3d(h/2, r*Cos(th),r*Sin(th));
    }
    glEnd();
    glColor3f(0.2,0.2,0.2);
    glBegin(GL_TRIANGLE_FAN);
    for (int th=0;th<=360;th+=10)
    {
            glVertex3d(-h/2, r*Cos(th),r*Sin(th));
    }
    glEnd();
    

    //  Undo transformations
    glPopMatrix();
}

void wheels()
{
    WheelRod(10,4,9, 0,0,90, 20);
    WheelRod(10, 4, -38, 0,0,90, 20);
    
    WheelStrip(12,4,9, 8, 5);
    WheelStrip(-12,4,9, 8, 5);

    WheelStrip(12,4,-38, 8, 5);
    WheelStrip(-12,4,-38, 8, 5);
}




void car()
{
    glPushMatrix();

    glTranslated(0,1,0);
    glRotated(180, 0,1,0);
    glScaled(0.5,0.5,0.5);
    wheels();
    CarNose();
    CarMonocoque();

    glPopMatrix();

}
