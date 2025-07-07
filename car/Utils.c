#include "Utils.h"
#include<math.h>
#include "../CSCI5229.h"

Object pickables[MAX_PICKABLE];
int    pickable_count = 0;

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

Vec3 sub( Vec3 a,  Vec3 b){
    return (Vec3){a.ax1-b.ax1, a.ax2-b.ax2, a.ax3-b.ax3};
}
float dot( Vec3 a,  Vec3 b){
    return a.ax1*b.ax1 + a.ax2*b.ax2 + a.ax3*b.ax3;
}

Vec3 Normalize(Vec3 v)
{
    float sum_sq = sqrt(v.ax1*v.ax1 + v.ax2*v.ax2 + v.ax3*v.ax3);

    if(sum_sq != 0)
    {
        v.ax1/= sum_sq;
        v.ax2/= sum_sq;
        v.ax3/= sum_sq;
    }
    return v;
}

void invertRigidBody(const GLdouble in[16], GLdouble out[16]) {
    out[0] = in[0];  out[1] = in[4];  out[2] = in[8];   out[3] = 0;
    out[4] = in[1];  out[5] = in[5];  out[6] = in[9];   out[7] = 0;
    out[8] = in[2];  out[9] = in[6];  out[10] = in[10]; out[11] = 0;
    out[12] = -(out[0]*in[12] + out[4]*in[13] + out[8]*in[14]);
    out[13] = -(out[1]*in[12] + out[5]*in[13] + out[9]*in[14]);
    out[14] = -(out[2]*in[12] + out[6]*in[13] + out[10]*in[14]);
    out[15] = 1;
}

void mult4(const GLdouble A[16], const GLdouble B[16], GLdouble C[16]) {
    for(int i=0;i<4;i++)for(int j=0;j<4;j++){
      C[j*4+i] = A[i]*B[j*4] 
               + A[i+4]*B[j*4+1]
               + A[i+8]*B[j*4+2]
               + A[i+12]*B[j*4+3];
    }
  }

void Model2World(float x, float y, float z, Vec3 * Vertices, int *size, const GLdouble MV[16])
{
    Vec3 vert = (Vec3){x, y, z};


    GLdouble invView[16], pureModel[16];
    invertRigidBody(viewM, invView);
    mult4(invView, MV, pureModel);

    Vec3 world;
    world.ax1 = pureModel[0]*vert.ax1 + pureModel[4]*vert.ax2 + pureModel[8]*vert.ax3  + pureModel[12];
    world.ax2 = pureModel[1]*vert.ax1 + pureModel[5]*vert.ax2 + pureModel[9]*vert.ax3  + pureModel[13];
    world.ax3 = pureModel[2]*vert.ax1 + pureModel[6]*vert.ax2 + pureModel[10]*vert.ax3 + pureModel[14];

    if (*size < 200) {
        Vertices[*size] = world;
        (*size)++;
    }

}


void registerPickableBox(const Vec3 modelCenter, const Vec3 modelHalf, float radius, int id, Vec3 * vertices, int Vert_size) {
    if (pickable_count >= MAX_PICKABLE) return;

    GLdouble MV[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, MV);

    GLdouble invView[16], pureModel[16];
    invertRigidBody(viewM, invView);
    mult4(invView, MV, pureModel);

    Vec3 world;
    world.ax1 = pureModel[0]*modelCenter.ax1 + pureModel[4]*modelCenter.ax2 + pureModel[8]*modelCenter.ax3  + pureModel[12];
    world.ax2 = pureModel[1]*modelCenter.ax1 + pureModel[5]*modelCenter.ax2 + pureModel[9]*modelCenter.ax3  + pureModel[13];
    world.ax3 = pureModel[2]*modelCenter.ax1 + pureModel[6]*modelCenter.ax2 + pureModel[10]*modelCenter.ax3 + pureModel[14];

    float sx = sqrtf(MV[0]*MV[0] + MV[1]*MV[1] + MV[2]*MV[2]);
    float sy = sqrtf(MV[4]*MV[4] + MV[5]*MV[5] + MV[6]*MV[6]);
    float sz = sqrtf(MV[8]*MV[8] + MV[9]*MV[9] + MV[10]*MV[10]);
    float worldRad = radius * fmaxf(fmaxf(sx,sy),sz);

    Vec3 we;
    we.ax1 = modelHalf.ax1 * sx;
    we.ax2 = modelHalf.ax2 * sy;
    we.ax3 = modelHalf.ax3 * sz;

    
    for(int i =0; i<pickable_count;i++)
        if(id == pickables[i].id)
            return;
            

    Vec3* vertsCopy = malloc(sizeof(Vec3) * Vert_size);
    if (!vertsCopy) {
        fprintf(stderr, "Failed to allocate memory for pickable vertices.\n");
        return;
    }
    memcpy(vertsCopy, vertices, sizeof(Vec3) * Vert_size);


    pickables[pickable_count++] = (Object){
        .id = id,
        .center = world,
        .dim = we,
        .radius = worldRad,
        .vertices = vertsCopy,
        .size = Vert_size,
        .bbox = modelHalf
    };
}



