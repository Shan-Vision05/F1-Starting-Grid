#include "Utils.h"
#include "CarParts.h"

void Wing_Flaps_F()
{
    Vec3 Start1 = {13.5355,25,98};
    Vec3 Start2 = {13.9855,26.35,101.6};

    Vec3 End1 = {-13.5355,25,98};
    Vec3 End2 = {-13.9855,26.35,101.6};

    Vec3 dir1   = { End1.ax1 - Start1.ax1, End1.ax2 - Start1.ax2, End1.ax3 - Start1.ax3 };
    Vec3 dir2   = { End2.ax1 - Start2.ax1, End2.ax2 - Start2.ax2, End2.ax3 - Start2.ax3 };
    

    int samples = 50;

    glBegin(GL_QUAD_STRIP);
    
    for(int i =0; i<=samples;i++)
    {
        float t = (float)i/(float)samples;
        Vec3 point1 = {
            Start1.ax1 + t * (dir1.ax1),
            Start1.ax2 + t * (dir1.ax2) -  3*Sin(180*t),
            Start1.ax3 + t * (dir1.ax3)
        };
        float curvDir = -3 * Cos(180*t)  * 3.14159265; 

        Vec3 T = {
            dir1.ax1,
            dir1.ax2 + curvDir, 
            dir1.ax3
        };
        Vec3 point2 = {
            Start2.ax1 + t * (dir2.ax1),
            Start2.ax2 + t * (dir2.ax2) -  3*Sin(180*t),
            Start2.ax3 + t * (dir2.ax3)
        };

       
    
        // --- vector across the strip ---
        Vec3 W = {
            point2.ax1 - point1.ax1,
            point2.ax2 - point1.ax2,
            point2.ax3 - point1.ax3
        };

        Vec3 N = cross(T, W);
        glNormal3f(N.ax1, N.ax2, N.ax3);
        glVertex3f(point1.ax1, point1.ax2, point1.ax3);
        glVertex3f(point2.ax1, point2.ax2, point2.ax3);
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);
    
    for(int i =0; i<=samples;i++)
    {
        float t = (float)i/(float)samples;
        Vec3 point1 = {
            Start1.ax1 + t * (dir1.ax1),
            Start1.ax2 + t * (dir1.ax2) -  3*Sin(180*t),
            Start1.ax3 + t * (dir1.ax3)
        };
        Vec3 point2 = {
            Start2.ax1 + t * (dir2.ax1),
            Start2.ax2 + t * (dir2.ax2) -  3*Sin(180*t),
            Start2.ax3 + t * (dir2.ax3)
        };
        float curvDir = -3 * Cos(180*t)  * 3.14159265; 

        Vec3 T = {
            dir1.ax1,
            dir1.ax2 + curvDir, 
            dir1.ax3
        };
        

       
    
        // --- vector across the strip ---
        Vec3 W = {
            point2.ax1 - point1.ax1,
            point2.ax2 - point1.ax2,
            point2.ax3 - point1.ax3
        };

        Vec3 N = cross(W, T);
        glNormal3f(N.ax1, N.ax2, N.ax3);
        glVertex3f(point1.ax1, point1.ax2-0.01, point1.ax3);
        glVertex3f(point2.ax1, point2.ax2-0.01, point2.ax3);
    }
    glEnd();
}

void Wing_Flaps_B()
{
    Vec3 Start1 = {13.5355+0.55,25+1.65,98+4.4};
    Vec3 Start2 = {14.5355,28,106};

    Vec3 End1 = {-13.5355-0.55,25+1.65,98+4.4};
    Vec3 End2 = {-14.5355,28,106};

    Vec3 dir1   = { End1.ax1 - Start1.ax1, End1.ax2 - Start1.ax2, End1.ax3 - Start1.ax3 };
    Vec3 dir2   = { End2.ax1 - Start2.ax1, End2.ax2 - Start2.ax2, End2.ax3 - Start2.ax3 };

    int samples = 50;

    glBegin(GL_QUAD_STRIP);
    
    for(int i =0; i<=samples;i++)
    {
        float t = (float)i/(float)samples;
        Vec3 point1 = {
            Start1.ax1 + t * (dir1.ax1),
            Start1.ax2 + t * (dir1.ax2) -  3*Sin(180*t),
            Start1.ax3 + t * (dir1.ax3)
        };
        

        Vec3 point2 = {
            Start2.ax1 + t * (dir2.ax1),
            Start2.ax2 + t * (dir2.ax2) -  3*Sin(180*t),
            Start2.ax3 + t * (dir2.ax3)
        };

        float curvDir = -3 * Cos(180*t)  * 3.14159265; 

        Vec3 T = {
            dir1.ax1,
            dir1.ax2 + curvDir, 
            dir1.ax3
        };
        
        // --- vector across the strip ---
        Vec3 W = {
            point2.ax1 - point1.ax1,
            point2.ax2 - point1.ax2,
            point2.ax3 - point1.ax3
        };

        Vec3 N = cross(T, W);
        glNormal3f(N.ax1, N.ax2, N.ax3);

        glVertex3f(point1.ax1, point1.ax2, point1.ax3);
        glVertex3f(point2.ax1, point2.ax2, point2.ax3);
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);
    
    for(int i =0; i<=samples;i++)
    {
        float t = (float)i/(float)samples;
        Vec3 point1 = {
            Start1.ax1 + t * (dir1.ax1),
            Start1.ax2 + t * (dir1.ax2) -  3*Sin(180*t),
            Start1.ax3 + t * (dir1.ax3)
        };
        

        Vec3 point2 = {
            Start2.ax1 + t * (dir2.ax1),
            Start2.ax2 + t * (dir2.ax2) -  3*Sin(180*t),
            Start2.ax3 + t * (dir2.ax3)
        };

        float curvDir = -3 * Cos(180*t)  * 3.14159265; 

        Vec3 T = {
            dir1.ax1,
            dir1.ax2 + curvDir, 
            dir1.ax3
        };
        
        // --- vector across the strip ---
        Vec3 W = {
            point2.ax1 - point1.ax1,
            point2.ax2 - point1.ax2,
            point2.ax3 - point1.ax3
        };

        Vec3 N = cross(W, T);
        glNormal3f(N.ax1, N.ax2, N.ax3);

        glVertex3f(point1.ax1, point1.ax2-0.01, point1.ax3);
        glVertex3f(point2.ax1, point2.ax2-0.01, point2.ax3);
    }
    glEnd();
}

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
    float dy = 25 - 12;
    if(side == 'r')
    {
        glBegin(GL_QUAD_STRIP);
        for(int i =0;i<=samples;i++)
        {
            float t = (float) i/ (float) samples;
            float x = -5*Sin(90 + 135 * t);

            float y = 12 + t * dy;
            float z1 = 102 - (2 + 2 * t);
            float z2 = 102 + (2 + 2 * t);

            float dxdT = -5 * Cos(90 + 135 * t) * (135 * 3.14159265/180.0f);
            float dydT = dy; 
            float dzdT = -2.0f;

            float wx = 1.0f;
            float wy = 0.0f;
            float wz = (z2 - z1); 

            Vec3 T = {dxdT, dydT, dzdT};
            Vec3 W = {wx, wy, -wz};

            Vec3 N = cross(T, W);  
            
            glNormal3f(N.ax1, N.ax2, N.ax3);
            glVertex3f(10+x, y, 102 - (2+2*t));
            glVertex3f(11+x, y, 102 + (2+2*t));
        }
        glEnd();
        glBegin(GL_QUAD_STRIP);
        for(int i =0;i<=samples;i++)
        {
            float t = (float) i/ (float) samples;
            float x = -5*Sin(90 + 135 * t) +0.01;

            float y = 12 + t * dy;
            float z1 = 102 - (2 + 2 * t);
            float z2 = 102 + (2 + 2 * t);

            float dxdT = -5 * Cos(90 + 135 * t) * (135 * 3.14159265/180.0f);
            float dydT = dy;
            float dzdT = -2.0f;


            float wx = 1.0f;
            float wy = 0.0f;
            float wz = (z2 - z1);

            Vec3 T = {dxdT, dydT, dzdT};
            Vec3 W = {wx, wy, wz};

            Vec3 N = cross(T, W);  
            
            glNormal3f(N.ax1, N.ax2, N.ax3);
            glVertex3f(10+x, y, 102 - (2+2*t));
            glVertex3f(11+x, y, 102 + (2+2*t));
        }
        glEnd();
    }
    else
    {
        glBegin(GL_QUAD_STRIP);
        for(int i =0;i<=samples;i++)
        {
            float t = (float) i/ (float) samples;
            float x = -5*Sin(90 + 135 * t);
            float y = 12 + t * dy;
            float z1 = 102 - (2 + 2 * t);
            float z2 = 102 + (2 + 2 * t);

            float dxdT = -5 * Cos(90 + 135 * t) * (135 * 3.14159265/180.0f);
            float dydT = dy; 
            float dzdT = -2.0f;

            float wx = 1.0f;
            float wy = 0.0f;
            float wz = (z2 - z1); 

            Vec3 T = {-dxdT, dydT, dzdT};
            Vec3 W = {wx, wy, -wz};

            Vec3 N = cross(T, W);  
            
            glNormal3f(N.ax1, N.ax2, N.ax3);
            glVertex3f(-(10+x), y, 102 - (2+2*t));
            glVertex3f(-(11+x), y, 102 + (2+2*t));
        }
        glEnd();

        glBegin(GL_QUAD_STRIP);
        for(int i =0;i<=samples;i++)
        {
            float t = (float) i/ (float) samples;
            float x = -5*Sin(90 + 135 * t) -0.01;
            float y = 12 + t * dy;
            float z1 = 102 - (2 + 2 * t);
            float z2 = 102 + (2 + 2 * t);

            float dxdT = -5 * Cos(90 + 135 * t) * (135 * 3.14159265/180.0f);
            float dydT = dy; 
            float dzdT = -2.0f;

            float wx = 1.0f;
            float wy = 0.0f;
            float wz = (z2 - z1); 

            Vec3 T = {-dxdT, dydT, dzdT};
            Vec3 W = {wx, wy, wz};

            Vec3 N = cross(T, W);  
            
            glNormal3f(N.ax1, N.ax2, N.ax3);
            glVertex3f(-(10+x), y, 102 - (2+2*t));
            glVertex3f(-(11+x), y, 102 + (2+2*t));
        }
        glEnd();

    }

    glBegin(GL_POLYGON);
    glNormal3f(0,1,0);
    glVertex3f(5, 12, 100);
    glVertex3f(6, 12, 104);
    glVertex3f(-6, 12, 104);
    glVertex3f(-5, 12, 100);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(0,-1,0);
    glVertex3f(5, 12-0.01, 100);
    glVertex3f(6, 12-0.01, 104);
    glVertex3f(-6, 12-0.01, 104);
    glVertex3f(-5, 12-0.01, 100);
    glEnd();


    glBegin(GL_POLYGON);
    glNormal3f(-1,0,0);
    glVertex3f(13.5355,25,98);
    glVertex3f(14.5355,25,106);
    glVertex3f(14.5355,28,106);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glVertex3f(13.5355+0.01,25,98);
    glVertex3f(14.5355+0.01,25,106);
    glVertex3f(14.5355+0.01,28,106);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glVertex3f(-13.5355,25,98);
    glVertex3f(-14.5355,25,106);
    glVertex3f(-14.5355,28,106);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(-1,0,0);
    glVertex3f(-13.5355-0.01,25,98);
    glVertex3f(-14.5355-0.01,25,106);
    glVertex3f(-14.5355-0.01,28,106);
    glEnd();

    Wing_Flaps_F();
    Wing_Flaps_B();

    glPopMatrix();
    glPopMatrix();
}


void RearWing()
{
    Wing_Holder('r');
    Wing_Holder('l');
}