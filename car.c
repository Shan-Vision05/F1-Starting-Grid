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

void CarNose(double r, double g, double b, unsigned int tex_nose, unsigned int tex_side)
{   
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();
    glTranslated(0, 1, 0);
    int samples = 50;
    glColor3f(r, g, b);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex_nose);
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
        glTexCoord2f(0.2, (1-t));
        glVertex3f(  -nose_w, point.y, point.z);
        glTexCoord2f(0.8, (1-t));
        glVertex3f(  nose_w, point.y, point.z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex_side);
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
        glTexCoord2f(1, (1-t));
        glVertex3f(  -nose_w, point.y, point.z);
        glTexCoord2f(0, (1-t));
        glVertex3f(  nose_w, point.y, point.z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex_side);

    // //Left Side of the nose
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point1 = GetPoint_Bezier(Nose_CP_Down, 4, t);
        Vec2 point2 = GetPoint_Bezier(Nose_CP_Top, 7, t);
        Vec2 d = GetTangent_Bezier(Nose_CP_Top, 7, t);
        Vec3 T = {0.0, d.y, d.z};
        Vec3 W = {0.0, point2.y-point1.y, point2.z - point1.z};
        Vec3 N = cross(W,T);

        float nose_w = 4 - 3 * t; // tapering as it reaches the tip
        glNormal3f(N.x, N.y, N.z);
        glTexCoord2f( (1-t), 0.35);
        glVertex3f(  nose_w, point1.y, point1.z);
        glTexCoord2f((1-t), 0.65);
        glVertex3f(  nose_w, point2.y, point2.z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, tex_side);
    

    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point1 = GetPoint_Bezier(Nose_CP_Down, 4, t);
        Vec2 point2 = GetPoint_Bezier(Nose_CP_Top, 7, t);
        Vec2 d = GetTangent_Bezier(Nose_CP_Top, 7, t);
        Vec3 T = {0.0, d.y, d.z};
        Vec3 W = {0.0, point1.y-point2.y, point1.z - point2.z};
        Vec3 N = cross(W,T);

        float nose_w = 4 - 3 * t; // tapering as it reaches the tip
        glNormal3f(N.x, N.y, N.z);
        glTexCoord2f( (1-t), 0.35);
        glVertex3f(  -nose_w, point1.y, point1.z);
        glTexCoord2f( (1-t), 0.65);
        glVertex3f(  -nose_w, point2.y, point2.z);
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);

    
    glPopMatrix();
}


void CarMonocoque(double r, double g, double b, unsigned int tex_end, unsigned int tex_side, unsigned int text_red)
{
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);


    glPushMatrix();
    glTranslated(0, 1, 0);
    int samples = 10;
    glColor3f(r, g, b);

    int angle = 220;
    int amp = 5;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, text_red);
    

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
        glTexCoord2f( (1-t), 0.0);
        glVertex3f(  -nose_w, point.y, point.z);
        glTexCoord2f( (1-t), 1.0);
        glVertex3f(  nose_w, point.y, point.z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, text_red);
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
        glTexCoord2f( (1-t), 0.0);
        glVertex3f(  -nose_w, point.y, point.z);
        glTexCoord2f( (1-t), 1.0);
        glVertex3f(  nose_w, point.y, point.z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex_side);

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
        glTexCoord2f( t, 0.0);
        glVertex3f(  nose_w, point1.y, point1.z);
        glTexCoord2f( t, 1.0);
        glVertex3f(  nose_w, point2.y, point2.z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex_side);
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
        glTexCoord2f( (1-t), 0.0);
        glVertex3f(  -nose_w, point1.y, point1.z);
        glTexCoord2f( (1-t), 1.0);
        glVertex3f(  -nose_w, point2.y, point2.z);
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);

    glColor3f(1, 1, 1);
    cube(0,2,-35, 2, 1.5, 4, 0, tex_end);

    
    glPopMatrix();
}

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




void car(unsigned int tex_end, unsigned int tex_wheel, unsigned int tex_rim, unsigned int tex_nose,
        unsigned int tex_nose_side, unsigned int text_side_strip)
{
    // Car 1
    glPushMatrix();

    // glTranslated(-20,1,15);
    glTranslated(0,1,0);
    glRotated(180, 0,1,0);
    glScaled(0.5,0.5,0.5);

    CarNose(0.8, 0.1,0.1, tex_nose, tex_nose_side);
    CarMonocoque(0.8,0.1,0.1, tex_end, text_side_strip, tex_nose_side);
    wheels(tex_wheel, tex_rim, tex_end);

    glPopMatrix();

}
