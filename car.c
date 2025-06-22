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

Vec3 cross(const Vec3 a, const Vec3 b) {
    Vec3 c;
    c.x = a.y*b.z - a.z*b.y;
    c.y = a.z*b.x - a.x*b.z;
    c.z = a.x*b.y - a.y*b.x;
    return c;
}


Vec2 GetPoint_Bezier(const Vec2 *CP, size_t n, float t)
{
    // Gives us the point on the Bezier curve at time step t
    Vec2 tmp[n];
    for(size_t i=0; i<n; ++i)
        tmp[i] = CP[i];

    for(size_t k=1; k<n; ++k){
        for(size_t i=0; i<n-k; ++i){
            float u = 1 - t;
            tmp[i].z = u*tmp[i].z + t*tmp[i+1].z;
            tmp[i].y = u*tmp[i].y + t*tmp[i+1].y;
        }
    }
    return tmp[0]; 
}

Vec2 GetTangent_Bezier(const Vec2 *CP, size_t n, float t)
{
    if (n < 2) return (Vec2){0,0};
    size_t d = n - 1;
    Vec2 tmp[d];
    for (size_t i = 0; i < d; ++i) {
        tmp[i].y = (CP[i+1].y - CP[i].y) * (float)d;
        tmp[i].z = (CP[i+1].z - CP[i].z) * (float)d;
    }
    return GetPoint_Bezier(tmp, d, t);
}

void CarNose(double r, double g, double b)
{   
    //0.8, 0.1, 0.1
    glPushMatrix();
    glTranslated(0, 1, 0);
    int samples = 10;
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_STRIP);

    //Top part of the Nose
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(Nose_CP_Top, 7, t);
        Vec2 d = GetTangent_Bezier(Nose_CP_Top, 7, t);
        Vec3 T = {0.0, d.y, d.z};
        Vec3 W = {-1.0, 0.0, 0.0};
        Vec3 N = cross(W,T);

        float nose_w = 4 - 3 * t; // tapering as it reaches the tip
        glNormal3f(N.x, N.y, N.z);
        glVertex3f(  -nose_w, point.y, point.z);
        glVertex3f(  nose_w, point.y, point.z);
    }
    glEnd();

    // Bottom Part of the nose
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(Nose_CP_Down, 4, t);
        Vec2 d = GetTangent_Bezier(Nose_CP_Down, 4, t);
        Vec3 T = {0.0, d.y, d.z};
        Vec3 W = {1.0, 0.0, 0.0};
        Vec3 N = cross(W,T);
        float nose_w = 4 - 3 * t; // tapering as it reaches the tip
        glNormal3f(N.x, N.y, N.z);
        glVertex3f(  -nose_w, point.y, point.z);
        glVertex3f(  nose_w, point.y, point.z);
    }
    glEnd();

    // //Left Side of the nose
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point1 = GetPoint_Bezier(Nose_CP_Down, 4, t);
        Vec2 point2 = GetPoint_Bezier(Nose_CP_Top, 7, t);
        Vec2 d = GetTangent_Bezier(Nose_CP_Top, 4, t);
        Vec3 T = {0.0, d.y, d.z};
        Vec3 W = {0.0, point2.y-point1.y, point2.z - point1.z};
        Vec3 N = cross(W,T);

        float nose_w = 4 - 3 * t; // tapering as it reaches the tip
        glNormal3f(N.x, N.y, N.z);
        glVertex3f(  nose_w, point1.y, point1.z);
        glVertex3f(  nose_w, point2.y, point2.z);
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point1 = GetPoint_Bezier(Nose_CP_Down, 4, t);
        Vec2 point2 = GetPoint_Bezier(Nose_CP_Top, 7, t);
        Vec2 d = GetTangent_Bezier(Nose_CP_Top, 4, t);
        Vec3 T = {0.0, d.y, d.z};
        Vec3 W = {0.0, point1.y-point2.y, point1.z - point2.z};
        Vec3 N = cross(W,T);

        float nose_w = 4 - 3 * t; // tapering as it reaches the tip
        glNormal3f(N.x, N.y, N.z);
        glVertex3f(  -nose_w, point1.y, point1.z);
        glVertex3f(  -nose_w, point2.y, point2.z);
    }

    glEnd();

    
    glPopMatrix();
}


void CarMonocoque(double r, double g, double b)
{
    glPushMatrix();
    glTranslated(0, 1, 0);
    int samples = 10;
    glColor3f(r, g, b);

    int angle = 220;
    int amp = 5;

    glBegin(GL_TRIANGLE_STRIP);
    //Top part of the Nose
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(Monocoque_CP_Top, 6, t);
        Vec2 d = GetTangent_Bezier(Monocoque_CP_Top, 6, t);
        Vec3 T = {0.0, d.y, d.z};
        Vec3 W = {1.0, 0.0, 0.0};
        Vec3 N = cross(W,T);

        
        float nose_w = 4 + amp * Sin(angle*t); // tapering as it reaches the end
        glNormal3f(N.x, N.y, N.z);
        glVertex3f(  -nose_w, point.y, point.z);
        glVertex3f(  nose_w, point.y, point.z);
    }
    glEnd();

    // Bottom Part of the nose
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(Monocoque_CP_Down, 5, t);
        Vec2 d = GetTangent_Bezier(Monocoque_CP_Down, 5, t);
        Vec3 T = {0.0, d.y, d.z};
        Vec3 W = {-1.0, 0.0, 0.0};
        Vec3 N = cross(W,T);

        float nose_w = 4 + amp * Sin(angle*t); // tapering as it reaches the end
        glNormal3f(N.x, N.y, N.z);
        glVertex3f(  -nose_w, point.y, point.z);
        glVertex3f(  nose_w, point.y, point.z);
    }
    glEnd();

    // //Left Side of the nose
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point1 = GetPoint_Bezier(Monocoque_CP_Down, 5, t);
        Vec2 point2 = GetPoint_Bezier(Monocoque_CP_Top, 6, t);
        Vec2 d = GetTangent_Bezier(Monocoque_CP_Top, 6, t);
        Vec3 T = {0.0, d.y, d.z};
        Vec3 W = {0.0, point1.y - point2.y, point1.z - point2.z};
        Vec3 N = cross(W,T);

        float nose_w = 4 + amp * Sin(angle*t); // tapering as it reaches the end

        glNormal3f(N.x, N.y, N.z);
        glVertex3f(  nose_w, point1.y, point1.z);
        glVertex3f(  nose_w, point2.y, point2.z);
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point1 = GetPoint_Bezier(Monocoque_CP_Down, 5, t);
        Vec2 point2 = GetPoint_Bezier(Monocoque_CP_Top, 6, t);
        Vec2 d = GetTangent_Bezier(Monocoque_CP_Top, 6, t);
        Vec3 T = {0.0, d.y, d.z};
        Vec3 W = {0.0, point2.y - point1.y, point2.z - point1.z};
        Vec3 N = cross(W,T);

        float nose_w = 4 + amp * Sin(angle*t); // tapering as it reaches the end
        glNormal3f(N.x, N.y, N.z);
        glVertex3f(  -nose_w, point1.y, point1.z);
        glVertex3f(  -nose_w, point2.y, point2.z);
    }

    glEnd();

    glColor3f(0.6, 0.1, 0.1);
    cube(0,2,-35, 2, 1.5, 4, 0);

    
    glPopMatrix();
}

void WheelRod(double x, double y, double z, double phi, double theta, double ro, double h)
{

    glPushMatrix();
    float r = 0.5;
    glTranslated(x,y,z);
    glRotated(phi, 1,0,0);
    glRotated(theta, 0,1,0);
    glRotated(ro, 0,0,1);
    glScaled(r,1.0,r);

    glColor3f(0.0, 0.7, 0.7);
    glBegin(GL_QUAD_STRIP);
    for (int th=0;th<=360;th+=30)
    {       glNormal3f(Cos(th),0,Sin(th));
            glVertex3d(Cos(th),0,Sin(th));
            glVertex3d(Cos(th),h,Sin(th));
    }
    glEnd();
    

    glPopMatrix();
}

void WheelStrip(double x, double y, double z, double h, double r)
{

    glPushMatrix();

    glTranslated(x,y,z);


    glColor3f(0.3,0.3,0.3);
    glBegin(GL_QUAD_STRIP);
    for (int th=0;th<=360;th+=10)
    {
        glNormal3f(0, r*Cos(th),r*Sin(th));
        glVertex3d(h/2, r*Cos(th),r*Sin(th));
        glVertex3d(-h/2, r*Cos(th), r*Sin(th));
    }
    glEnd();

    // glColor3f(0.2,0.2,0.2);
    glBegin(GL_TRIANGLE_FAN);
    for (int th=0;th<=360;th+=10)
    {
        glNormal3f(1,0,0);
        glVertex3d(h/2, r*Cos(th),r*Sin(th));
    }
    glEnd();
    // glColor3f(0.2,0.2,0.2);
    glBegin(GL_TRIANGLE_FAN);
    for (int th=0;th<=360;th+=10)
    {
        glNormal3f(-1,0,0);
        glVertex3d(-h/2, r*Cos(th),r*Sin(th));
    }
    glEnd();
    

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
    // Car 1
    glPushMatrix();

    glTranslated(-20,1,15);
    glRotated(180, 0,1,0);
    glScaled(0.5,0.5,0.5);

    CarNose(0.8, 0.1,0.1);
    CarMonocoque(0.8,0.1,0.1);
    wheels();

    glPopMatrix();

    // Car 2
    glPushMatrix();

    glTranslated(20,1,-30);
    glRotated(180, 0,1,0);
    glScaled(0.5,0.5,0.5);

    CarNose(0.8, 0.1, 0.1);
    CarMonocoque(0.8, 0.1, 0.1);
    wheels();
    
    glPopMatrix();

    // // Car 3
    glPushMatrix();

    glTranslated(20,1,30);
    glRotated(180, 0,1,0);
    glScaled(0.5,0.5,0.5);

    CarNose(0.1, 0.8, 0.1);
    CarMonocoque(0.1, 0.8, 0.1);
    wheels();
    
    glPopMatrix();

    // //Car 4
    glPushMatrix();

    glTranslated(-20,1,75);
    glRotated(180, 0,1,0);
    glScaled(0.5,0.5,0.5);

    CarNose(0.1, 0.8, 0.1);
    CarMonocoque(0.1, 0.8, 0.1);
    wheels();
    
    glPopMatrix();

}
