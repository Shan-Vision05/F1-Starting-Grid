#ifndef CARUTILS_H
#define CARUTILS_H

#include "../CSCI5229.h"

#define MAX_PICKABLE 512
extern Object pickables[MAX_PICKABLE];
extern int      pickable_count ;

Vec2 GetPoint_Bezier(const Vec2 *CP, int n, float t);
Vec2 GetTangent_Bezier(const Vec2 *CP, int n, float t);
Vec3 cross(const Vec3 a, const Vec3 b);
Vec3 sub( Vec3 a,  Vec3 b);
float dot( Vec3 a,  Vec3 b);
Vec3 Normalize(Vec3 v);
void registerPickableBox(const Vec3 modelCenter, const Vec3 modelHalf, float radius, int id, Vec3 * vertices, int Vert_size);
void Model2World(float x, float y, float z, Vec3 * Vertices, int *size, const GLdouble MV[16]);

#endif