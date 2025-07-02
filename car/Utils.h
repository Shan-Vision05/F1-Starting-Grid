#ifndef CARUTILS_H
#define CARUTILS_H

#include "../CSCI5229.h"



Vec2 GetPoint_Bezier(const Vec2 *CP, int n, float t);
Vec2 GetTangent_Bezier(const Vec2 *CP, int n, float t);
Vec3 cross(const Vec3 a, const Vec3 b);
Vec3 Normalize(Vec3 v);

#endif