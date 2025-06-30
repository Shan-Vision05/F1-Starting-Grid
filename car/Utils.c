#include "Utils.h"

Vec2 GetPoint_Bezier(const Vec2 *CP, int n, float t)
{
    // Gives us the point on the Bezier curve at time step t
    Vec2 tmp[n];
    for(int i=0; i<n; ++i)
        tmp[i] = CP[i];

    for(int k=1; k<n; ++k){
        for(int i=0; i<n-k; ++i){
            float u = 1 - t;
            tmp[i].ax1 = u*tmp[i].ax1 + t*tmp[i+1].ax1;
            tmp[i].ax2 = u*tmp[i].ax2 + t*tmp[i+1].ax2;
        }
    }
    return tmp[0]; 
}

Vec2 GetTangent_Bezier(const Vec2 *CP, int n, float t)
{
    if (n < 2) return (Vec2){0,0};
    int d = n - 1;
    Vec2 tmp[d];
    for (int i = 0; i < d; ++i) {
        tmp[i].ax1 = (CP[i+1].ax1 - CP[i].ax1) * (float)d;
        tmp[i].ax2 = (CP[i+1].ax2 - CP[i].ax2) * (float)d;
    }
    return GetPoint_Bezier(tmp, d, t);
}

Vec3 cross(const Vec3 a, const Vec3 b) {
    Vec3 c;
    c.ax1 = a.ax2*b.ax3 - a.ax3*b.ax2;
    c.ax2 = a.ax3*b.ax1 - a.ax1*b.ax3;
    c.ax3 = a.ax1*b.ax2 - a.ax2*b.ax1;
    return c;
}
