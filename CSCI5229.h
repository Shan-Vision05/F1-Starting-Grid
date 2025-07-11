// This Header file is taken from example 12 and modified according to mt requirement.

#ifndef CSCI5229
#define CSCI5229

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

// GLEW _MUST_ be included first
#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  Get all GL prototypes
#define GL_GLEXT_PROTOTYPES
//  Select SDL, SDL2, GLFW or GLUT
#if defined(SDL2)
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#elif defined(SDL)
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#elif defined(GLFW)
#include <GLFW/glfw3.h>
#elif defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
//  Make sure GLU and GL are included
#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
// Tell Xcode IDE to not gripe about OpenGL deprecation
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif
//  Default resolution
//  For Retina displays compile with -DRES=2
#ifndef RES
#define RES 1
#endif

//  cos and sin in degrees
#define Cos(th) cos(3.14159265/180*(th))
#define Sin(th) sin(3.14159265/180*(th))
#define RAD2DEG(x) ((x)*180.0/3.14159265)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __GNUC__
void Print(const char* format , ...) __attribute__ ((format(printf,1,2)));
#else
void Print(const char* format , ...);
#endif
typedef struct { float ax1, ax2; } Vec2;
typedef struct { float ax1, ax2, ax3; } Vec3;


typedef struct {
    int id;
    Vec3   center;
    Vec3 dim;
    float  radius;
    Vec3 * vertices;
    int size;
    Vec3 bbox;
} Object;

extern GLdouble viewM[16];

void ErrCheck(const char* where);
void Fatal(const char* format , ...);
unsigned int LoadTexBMP(const char* file);
extern float ambient;
extern float diffuse;
extern float specular;
extern float emission;
extern float shiny;

#ifdef __cplusplus
}
#endif

#endif
