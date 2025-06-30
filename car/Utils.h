#ifndef CARUTILS_H
#define CARUTILS_H

#include "../CSCI5229.h"

typedef struct { float ax1, ax2; } Vec2;
typedef struct { float ax1, ax2, ax3; } Vec3;

Vec2 GetPoint_Bezier(const Vec2 *CP, int n, float t);
Vec2 GetTangent_Bezier(const Vec2 *CP, int n, float t);
Vec3 cross(const Vec3 a, const Vec3 b);

#endif