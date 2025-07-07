#include "Utils.h"
#include "CarParts.h"

Vec2 W_Nose_CP_Top[7] = {
    {1, 10},
    {0, 11},
    {1,12},
    {5,14},
    {10,15},
    {20,17},
};

Vec2 W_Nose_CP_Down[4] ={
    {1,10},
    {5,11},
    {15,12},
    {20,13},
};

Vec2 W_Wing_Blade_Left[4] ={
    // {-20,8},
    // {-19,6},
    // {-15,9},
    // {-4,10},
    // {0,8},
    {4,10},
    {15,9},
    {19,6},
    {20,8}
};

Vec2 W_Tip_Blade_F[3] ={
    {-4, 10},
    {0, 8},
    {4, 10}
};
Vec2 W_Tip_Blade_B[3] ={
    {-4, 10},
    {0, 9},
    {4, 10}
};


Vec2 W_Side_Blade_T[7] ={
    {8.5, 7},
    {7, 11},
    {8.5, 15},
    {6, 12},
    {2, 12},
    {-1, 8},
    {-1, 6},
    
};

Vec2 W_Side_Blade_B[2] ={
    {8.5, 7},
    {-1, 6}
};

Vec2 W_Flaps[4] ={
    {15,9},
    {19,6},
    {20,8}
};

Vec2 W_Nose_Back_T[5] ={
    {20,17},
    {30,19},
    {35, 19},
    {40, 20},
    {44, 20}
};

Vec2 W_Nose_Back_B[3] ={
    {20,13},
    {32, 12.5},
    {44, 12}
};


void Nose(unsigned int tex_top, unsigned int tex_red)
{
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);



    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    // glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,tex_top);

    glPushMatrix();
    int samples = 50;
    glColor3f(0.5, 0.0, 0.0);


    glBegin(GL_TRIANGLE_STRIP);

    //Top part of the Nose
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(W_Nose_CP_Top, 6, t);
        Vec2 d = GetTangent_Bezier(W_Nose_CP_Top, 6, t);
        Vec3 T = {0.0, d.ax2, d.ax1};
        Vec3 W = {-1.0, 0.0, 0.0};
        Vec3 N = cross(W,T);

        float nose_w = 1.2 + 1.6 * t; // tapering as it reaches the tip
        glNormal3f(N.ax1, N.ax2, N.ax3);
        glTexCoord2f(0,t/2);glVertex3f(  -nose_w, point.ax2, point.ax1);
        glTexCoord2f(1,t/2);glVertex3f(  nose_w, point.ax2, point.ax1);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    // glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,tex_red);

    // Bottom Part of the nose
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(W_Nose_CP_Down, 4, t);
        Vec2 d = GetTangent_Bezier(W_Nose_CP_Down, 4, t);
        Vec3 T = {0.0, d.ax2, d.ax1};
        Vec3 W = {1.0, 0.0, 0.0};
        Vec3 N = cross(W,T);
        float nose_w = 1.2 + 1.6 * t; // tapering as it reaches the tip
        glNormal3f(N.ax1, N.ax2, N.ax3);
        glTexCoord2f(1,t);glVertex3f(  -nose_w, point.ax2, point.ax1);
        glTexCoord2f(0,t);glVertex3f(  nose_w, point.ax2, point.ax1);
    }
    glEnd();


    // //Left Side of the nose
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point1 = GetPoint_Bezier(W_Nose_CP_Down, 4, t);
        Vec2 point2 = GetPoint_Bezier(W_Nose_CP_Top, 6, t);
        Vec2 d = GetTangent_Bezier(W_Nose_CP_Top, 6, t);
        float nose_w = 1.2 + 1.6 * t; // tapering as it reaches the tip

        Vec3 T = {-1.6, d.ax2, d.ax1};
        Vec3 W = {0.0, point2.ax2-point1.ax2, point2.ax1 - point1.ax1};
        Vec3 N = cross(W,T);

        
        glNormal3f(N.ax1, N.ax2, N.ax3);
        glTexCoord2f(0,t);glVertex3f(  nose_w, point1.ax2, point1.ax1);
        glTexCoord2f(1,t);glVertex3f(  nose_w, point2.ax2, point2.ax1);
    }
    glEnd();

    // Right Side of the Nose
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point1 = GetPoint_Bezier(W_Nose_CP_Down, 4, t);
        Vec2 point2 = GetPoint_Bezier(W_Nose_CP_Top, 6, t);
        Vec2 d = GetTangent_Bezier(W_Nose_CP_Top, 6, t);
        float nose_w = 1.2 + 1.6 * t; // tapering as it reaches the tip
        Vec3 T = {1.6, d.ax2, d.ax1};
        Vec3 W = {0.0, point1.ax2-point2.ax2, point1.ax1 - point2.ax1};
        Vec3 N = cross(W,T);

        
        glNormal3f(N.ax1, N.ax2, N.ax3);
        glTexCoord2f(0,t);glVertex3f(  -nose_w, point1.ax2, point1.ax1);
        glTexCoord2f(1,t);glVertex3f(  -nose_w, point2.ax2, point2.ax1);
    }

    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void Nose_Back(unsigned int tex_top, unsigned int red)
{
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);



    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    // glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,tex_top);

    glPushMatrix();
    int samples = 50;
    glColor3f(0.5, 0.0, 0.0);


    glBegin(GL_TRIANGLE_STRIP);

    //Top part of the Nose
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(W_Nose_Back_T, 5, t);
        Vec2 d = GetTangent_Bezier(W_Nose_Back_T, 5, t);
        Vec3 T = {0.0, d.ax2, d.ax1};
        Vec3 W = {-1.0, 0.0, 0.0};
        Vec3 N = cross(W,T);

        float nose_w = 2.8 + 1.6 * t; // tapering as it reaches the tip
        glNormal3f(N.ax1, N.ax2, N.ax3);
        glTexCoord2f(1,t/2+0.5);glVertex3f(  -nose_w, point.ax2, point.ax1);
        glTexCoord2f(0,t/2+0.5);glVertex3f(  nose_w, point.ax2, point.ax1);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,red);

    // Bottom Part of the nose
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(W_Nose_Back_B, 3, t);
        Vec2 d = GetTangent_Bezier(W_Nose_Back_B, 3, t);
        Vec3 T = {0.0, d.ax2, d.ax1};
        Vec3 W = {1.0, 0.0, 0.0};
        Vec3 N = cross(W,T);
        float nose_w = 2.8 + 1.6 * t; // tapering as it reaches the tip
        glNormal3f(N.ax1, N.ax2, N.ax3);
        glTexCoord2f(0,t);glVertex3f(  -nose_w, point.ax2, point.ax1);
        glTexCoord2f(1,t);glVertex3f(  nose_w, point.ax2, point.ax1);
    }
    glEnd();


     // //Left Side of the nose
     glBegin(GL_TRIANGLE_STRIP);
     for(int i=0;i<=samples;i++)
     {
         float t = (float)i / (float)samples;
         Vec2 point1 = GetPoint_Bezier(W_Nose_Back_B, 3, t);
         Vec2 point2 = GetPoint_Bezier(W_Nose_Back_T, 5, t);
         Vec2 d = GetTangent_Bezier(W_Nose_Back_T, 5, t);
         float nose_w = 2.8 + 1.6 * t; // tapering as it reaches the tip
 
         Vec3 T = {-1.6, d.ax2, d.ax1};
         Vec3 W = {0.0, point2.ax2-point1.ax2, point2.ax1 - point1.ax1};
         Vec3 N = cross(W,T);
 
         
         glNormal3f(N.ax1, N.ax2, N.ax3);
         glTexCoord2f(0,t);glVertex3f(  nose_w, point1.ax2, point1.ax1);
         glTexCoord2f(1,t);glVertex3f(  nose_w, point2.ax2, point2.ax1);
     }
     glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point1 = GetPoint_Bezier(W_Nose_Back_B, 3, t);
        Vec2 point2 = GetPoint_Bezier(W_Nose_Back_T, 5, t);
        Vec2 d = GetTangent_Bezier(W_Nose_Back_T, 5, t);
        float nose_w = 2.8 + 1.6 * t; // tapering as it reaches the tip
        Vec3 T = {1.6, d.ax2, d.ax1};
        Vec3 W = {0.0, point1.ax2-point2.ax2, point1.ax1 - point2.ax1};
        Vec3 N = cross(W,T);

        
        glNormal3f(N.ax1, N.ax2, N.ax3);
        glTexCoord2f(0,t);glVertex3f(  -nose_w, point1.ax2, point1.ax1);
        glTexCoord2f(1,t);glVertex3f(  -nose_w, point2.ax2, point2.ax1);
    }

    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void WingBladeFirst(int tipF, float x, float y, float z, int isFirst, unsigned int carbon_fiber)
{
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);



    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    // glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,carbon_fiber);

    int samples = 50;

    glPushMatrix();

    
    glTranslated(x, y, z);
    glRotated(-10, 1,0,0);
    
    glPushMatrix();
    
    glColor3f(0.3, 0.3, 0.3);


    glBegin(GL_TRIANGLE_STRIP);

    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(W_Wing_Blade_Left, 4, t);

        float nose_w = 4*Sin(90*t); // tapering as it reaches the tip

        Vec2 d = GetTangent_Bezier(W_Wing_Blade_Left, 4, t);
        Vec3 T = {d.ax1, d.ax2, 0};
        Vec3 W = {0, 0.0, -4*90*Cos(90*t)* (3.14159/180) };
        Vec3 N = cross(T,W);

        
        glNormal3f(N.ax1, N.ax2, N.ax3);

        glTexCoord2f(0,t);glVertex3f(  point.ax1, point.ax2, -2 + nose_w);
        glTexCoord2f(1,t);glVertex3f(  point.ax1, point.ax2, nose_w);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotated(180, 0,1,0);
    glColor3f(0.6, 0.6, 0.6);


    glBegin(GL_TRIANGLE_STRIP);

    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(W_Wing_Blade_Left, 4, t);

        float nose_w = 4*Sin(90*t); // tapering as it reaches the tip
        Vec2 d = GetTangent_Bezier(W_Wing_Blade_Left, 4, t);
        Vec3 T = {d.ax1, d.ax2, 0};
        Vec3 W = {0, 0.0, -4*90*Cos(90*t)* (3.14159/180)};
        Vec3 N = cross(T,W);

        
        glNormal3f(N.ax1, N.ax2, N.ax3);
        glTexCoord2f(0,t);glVertex3f(  point.ax1, point.ax2, 2 - nose_w);
        glTexCoord2f(1,t);glVertex3f(  point.ax1, point.ax2, - nose_w);
    }
    glEnd();
    glPopMatrix();

    // Blade Tip


    glPushMatrix();

    glColor3f(0.3, 0.3, 0.3);

    glBegin(GL_TRIANGLE_STRIP);

    for(int i=0;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point1 = GetPoint_Bezier(W_Tip_Blade_F, 3, t);
        Vec2 point2 = GetPoint_Bezier(W_Tip_Blade_B, 3, t);

        float dz = -tipF*180*Cos(180*t) * (3.14159/180);

        Vec2 d = GetTangent_Bezier(W_Tip_Blade_F, 3, t);
        Vec3 T = {d.ax1, d.ax2, dz};
        Vec3 W = {point2.ax1 - point1.ax1, point2.ax2 - point1.ax2, (-0.5f*Sin(180*t)) - (-2 - tipF*Sin(180*t)) };
        Vec3 N = cross(W, T);

        glNormal3f(N.ax1, N.ax2, N.ax3);
        glTexCoord2f(0,t);glVertex3f(  point1.ax1, point1.ax2, -2 - tipF*Sin(180*t));
        glTexCoord2f(1,t);glVertex3f(  point2.ax1, point2.ax2, -0.5* Sin(180*t));
    }
    glEnd();
    glPopMatrix();

    if(isFirst)
    {


        glPushMatrix();
        glTranslated(0, 1.8, 2.5);
        glRotated(5,1,0,0);
        glColor3f(0.3, 0.3, 0.3);


        glBegin(GL_TRIANGLE_STRIP);

        for(int i=0;i<=samples;i++)
        {
            float t = (float)i / (float)samples;
            Vec2 point1 = GetPoint_Bezier(W_Side_Blade_T, 7, t);
            Vec2 point2 = GetPoint_Bezier(W_Side_Blade_B, 2, t);

            glNormal3f(1, 0,0);
            glTexCoord2f(0,t);glVertex3f(  20, point1.ax2, point1.ax1);
            glTexCoord2f(1,t);glVertex3f(  20, point2.ax2, point2.ax1);
        }
        glEnd();

        glBegin(GL_TRIANGLE_STRIP);

        for(int i=0;i<=samples;i++)
        {
            float t = (float)i / (float)samples;
            Vec2 point1 = GetPoint_Bezier(W_Side_Blade_T, 7, t);
            Vec2 point2 = GetPoint_Bezier(W_Side_Blade_B, 2, t);

            glNormal3f(-1, 0,0);
            glTexCoord2f(0,t);glVertex3f(  19.99, point1.ax2, point1.ax1);
            glTexCoord2f(1,t);glVertex3f(  19.99, point2.ax2, point2.ax1);
        }
        glEnd();

        glPopMatrix();

        glPushMatrix();
        glTranslated(0, 1.8, 2.5);
        glRotated(5,1,0,0);
        glColor3f(0.3, 0.3, 0.3);


        glBegin(GL_TRIANGLE_STRIP);

        for(int i=0;i<=samples;i++)
        {
            float t = (float)i / (float)samples;
            Vec2 point1 = GetPoint_Bezier(W_Side_Blade_T, 7, t);
            Vec2 point2 = GetPoint_Bezier(W_Side_Blade_B, 2, t);
            
            glNormal3f(-1, 0,0);
            glTexCoord2f(0,t);glVertex3f(  -20, point1.ax2, point1.ax1);
            glTexCoord2f(1,t);glVertex3f(  -20, point2.ax2, point2.ax1);
        }
        glEnd();

        glBegin(GL_TRIANGLE_STRIP);

        for(int i=0;i<=samples;i++)
        {
            float t = (float)i / (float)samples;
            Vec2 point1 = GetPoint_Bezier(W_Side_Blade_T, 7, t);
            Vec2 point2 = GetPoint_Bezier(W_Side_Blade_B, 2, t);

            glNormal3f(1, 0,0);
            glTexCoord2f(0,t);glVertex3f(  -19.9, point1.ax2, point1.ax1);
            glTexCoord2f(1,t);glVertex3f(  -19.9, point2.ax2, point2.ax1);
        }
        glEnd();

        glPopMatrix();
                
    }




    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void WingBladeLast(float x, float y, float z, int flip, unsigned int carbon_fiber)
{
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);



    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    // glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,carbon_fiber);
    int samples = 50;

    glPushMatrix();

    
    glTranslated(x, y, z);
    glRotated(-10, 1,0,0);
    
    glPushMatrix();
    
    glColor3f(0.3, 0.3, 0.3);

    glBegin(GL_TRIANGLE_STRIP);

    for(int i= (int) samples/4;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(W_Wing_Blade_Left, 4, t);

        float nose_w = 4*Sin(90*t); // tapering as it reaches the tip
        float dz = 4*90*Cos(90*t) * (3.14159/180);

        Vec2 d = GetTangent_Bezier(W_Wing_Blade_Left, 4, t);
        Vec3 T = {d.ax1, d.ax2, dz};
        Vec3 W = {0, 0, (nose_w -2*(1-t))-(-2 + nose_w) };
        Vec3 N = cross(W, T);

        glNormal3f(N.ax1, N.ax2, N.ax3);

        glTexCoord2f(0,t);glVertex3f(  point.ax1, point.ax2, -2 + nose_w);
        glTexCoord2f(1,t);glVertex3f(  point.ax1, point.ax2, nose_w -2*(1-t));
    }
    glEnd();

    glPopMatrix();


    glPushMatrix();
    glRotated(180, 0,1,0);
    glColor3f(0.3, 0.3, 0.3);

    glBegin(GL_TRIANGLE_STRIP);

    for(int i= (int) samples/4;i<=samples;i++)
    {
        float t = (float)i / (float)samples;
        Vec2 point = GetPoint_Bezier(W_Wing_Blade_Left, 4, t);

        float nose_w = 4*Sin(90*t); // tapering as it reaches the tip
        float dz = 4*90*Cos(90*t) * (3.14159/180);

        Vec2 d = GetTangent_Bezier(W_Wing_Blade_Left, 4, t);
        Vec3 T = {d.ax1, d.ax2, dz};
        Vec3 W = {0, 0, (-nose_w+2*(1-t))-(2 - nose_w) };
        Vec3 N = cross(T, W);

        glNormal3f(N.ax1, N.ax2, N.ax3);
        glTexCoord2f(0,t);glVertex3f(  point.ax1, point.ax2, 2 - nose_w);
        glTexCoord2f(1,t);glVertex3f(  point.ax1, point.ax2, -nose_w+2*(1-t));
    }
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

}

void Wing(unsigned int tex_carbonFiber, unsigned int tex_Nose_Top, unsigned int tex_red)
{
    glPushMatrix();
    Nose(tex_Nose_Top, tex_red);
    Nose_Back(tex_Nose_Top, tex_red);
    WingBladeFirst(2, 0, 1.5, 3, 1, tex_carbonFiber);
    WingBladeFirst(0, 0, 2, 5.5, 0, tex_carbonFiber);
    WingBladeFirst(0, 0, 2.5, 8, 0, tex_carbonFiber);

    WingBladeLast(0, 3, 10.5, 0, tex_carbonFiber);


    glPopMatrix();
}


