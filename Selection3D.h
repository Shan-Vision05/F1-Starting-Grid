#ifndef SELECTION3D_H
#define SELECTION3D_H

typedef struct {
    int id;
    char name[64]; 
    float x, y, z;          // position
    float w, h, d;          // bounding box dimensions (width, height, depth)
    int isSelected;
  } Object;

extern int numSelectableObjects ;
extern int selectedObjectID ;
extern int isDragging;
extern int lastMouseX, lastMouseY;

#define MAX_SELECTABLE_OBJECTS 40
extern Object selectableObjects[MAX_SELECTABLE_OBJECTS];

void initializeObjects();
void renderSelectionHighlight();
float rayBoxIntersection(float rayStartX, float rayStartY, float rayStartZ,
    float rayDirX, float rayDirY, float rayDirZ,
    float boxMinX, float boxMinY, float boxMinZ,
    float boxMaxX, float boxMaxY, float boxMaxZ);
int getObjectAtMouse(int mouseX, int mouseY);
void selectObject(int objectID) ;
#endif
