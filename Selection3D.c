#include "CSCI5229.h"
#include "Selection3D.h"

  
  // Global selection variables
  
  Object selectableObjects[MAX_SELECTABLE_OBJECTS];
  int numSelectableObjects = 0;
  int selectedObjectID = -1;
  int isDragging = 0;
  int lastMouseX = 0, lastMouseY = 0;
  
  void initializeObjects() {
    numSelectableObjects = 0;
    
    Object cube1 = {
        0,  
        "Car",                          // id
        -50, 0.6, -1.90,               // position (center of cake)
        4, 2, 8,           // bounding box dimensions
         // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = cube1;
    
    Object cube2 = {
        1, 
        "Light Pole 1",                           // id
        -40.1, 2.7, 6,               // position
        1.2, 5.8, 2.2,           // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = cube2;

    Object garages = {
        2, 
        "Garages",                           // id
        -20.9, 1.8, 2.4,               // position
        10, 4.8, 88.6,           // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = garages;

    Object GransStand1_Roof = {
        3, 
        "Grand Stand 1 Roof",                           // id
        -65.00, 7.30, -0.00,               // position
        10.00, 2.20, 51.60,           // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = GransStand1_Roof;

    Object GransStand1 = {
        4, 
        "Grand Stand 1",                           // id
        -65.00, 1.70, -0.00,               // position
        10.00, 4.40, 51.60,           // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = GransStand1;

    Object GransStand2 = {
        5, 
        "Grand Stand 2",                           // id
        63.00, 1.70, -0.00,               // position
        10.00, 4.40, 51.60,           // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = GransStand2;

    Object StartLights = {
        6, 
        "Start Lights",                           // id
        -50.00, 3.40, -49.90,               // position
        3.00, 1.80, 0.40,           // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = StartLights;

    Object lp2 = {
        7, 
        "Light Pole 2",                           // id
        -40.10, 2.80, -8.00,               // position
        2.00, 5.40, 1.40,           // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = lp2;

    Object lp3 = {
        8, 
        "Light Pole 3",                           // id
        -40.20, 2.70, 20.00,               // position
        1.80, 5.60, 1.00,           // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = lp3;

    Object lp4 = {
        9, 
        "Light Pole 4",                           // id
        -40.20, 2.70, 34.00,               // position
        1.80, 5.60, 1.00,          // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = lp4;

    Object lp5 = {
        10, 
        "Light Pole 5",                           // id
        -40.20, 2.70, 48.00,               // position
        1.80, 5.60, 1.00,          // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = lp5;

    Object lp6 = {
        11, 
        "Light Pole 6",                           // id
        -40.20, 2.70, -22.00,               // position
        1.80, 5.60, 1.00,          // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = lp6;

    Object lp7 = {
        12, 
        "Light Pole 7",                           // id
        -40.20, 2.70, -36.00,               // position
        1.80, 5.60, 1.00,           // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = lp7;

    Object lp8 = {
        13, 
        "Light Pole 8",                           // id
        -40.20, 2.70, -50.00,               // position
        1.80, 5.60, 1.00,           // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = lp8;

    Object lp9 = {
        14, 
        "Light Pole 9",                           // id
        -59.90, 2.90, 48.00,               // position
        1.80, 5.60, 1.00,           // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = lp9;

    Object lp10 = {
        15, 
        "Light Pole 10",                           // id
        -59.90, 2.90, 34.00,               // position
        1.80, 5.60, 1.00,          // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = lp10;

    Object lp11 = {
        16, 
        "Light Pole 11",                           // id
        -59.90, 2.90, 20.00,               // position
        1.80, 5.60, 1.00,           // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = lp11;

    Object lp12 = {
        17, 
        "Light Pole 12",                           // id
        -59.90, 2.90, 6.00,               // position
        1.80, 5.60, 1.00,           // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = lp12;

    Object lp13 = {
        18, 
        "Light Pole 13",                           // id
        -59.90, 2.90, -8.00,               // position
        1.80, 5.60, 1.00,          // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = lp13;

    Object lp14 = {
        19, 
        "Light Pole 14",                           // id
        -59.90, 2.90, -22.00,               // position
        1.80, 5.60, 1.00,           // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = lp14;

    Object lp15 = {
        20, 
        "Light Pole 15",                           // id
        -59.90, 2.90, -36.00,               // position
        1.80, 5.60, 1.00,           // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = lp15;

    Object lp16 = {
        21, 
        "Light Pole 16",                           // id
        -59.90, 2.90, -50.00,               // position
        1.80, 5.60, 1.00,           // bounding box dimensions
           // name
        0,                 // isSelected
    };
    selectableObjects[numSelectableObjects++] = lp16;

  }
  
  void renderSelectionHighlight() {
    if (selectedObjectID < 0) return;
    
    for (int i = 0; i < numSelectableObjects; i++) {
        const Object* obj = &selectableObjects[i];
        if (obj->isSelected) {
            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            // Bright wireframe color
            glColor4f(1.0f, 0.0f, 1.0f, 0.9f); // Magenta wireframe for cakes
            if (obj->id == 12) { // Refrigerator gets different color
                glColor4f(0.0f, 1.0f, 1.0f, 0.9f); // Cyan for refrigerator
            }
            glLineWidth(3.0f); // Thick wireframe lines
            
            glPushMatrix();
            glTranslatef(obj->x, obj->y, obj->z);
            
            // Draw wireframe box - 12 edges of a cube
            glBegin(GL_LINES);
            
            // Bottom face (4 edges)
            glVertex3f(-obj->w/2, -obj->h/2, -obj->d/2); glVertex3f( obj->w/2, -obj->h/2, -obj->d/2);
            glVertex3f( obj->w/2, -obj->h/2, -obj->d/2); glVertex3f( obj->w/2, -obj->h/2,  obj->d/2);
            glVertex3f( obj->w/2, -obj->h/2,  obj->d/2); glVertex3f(-obj->w/2, -obj->h/2,  obj->d/2);
            glVertex3f(-obj->w/2, -obj->h/2,  obj->d/2); glVertex3f(-obj->w/2, -obj->h/2, -obj->d/2);
            
            // Top face (4 edges)
            glVertex3f(-obj->w/2,  obj->h/2, -obj->d/2); glVertex3f( obj->w/2,  obj->h/2, -obj->d/2);
            glVertex3f( obj->w/2,  obj->h/2, -obj->d/2); glVertex3f( obj->w/2,  obj->h/2,  obj->d/2);
            glVertex3f( obj->w/2,  obj->h/2,  obj->d/2); glVertex3f(-obj->w/2,  obj->h/2,  obj->d/2);
            glVertex3f(-obj->w/2,  obj->h/2,  obj->d/2); glVertex3f(-obj->w/2,  obj->h/2, -obj->d/2);
            
            // Vertical edges (4 edges)
            glVertex3f(-obj->w/2, -obj->h/2, -obj->d/2); glVertex3f(-obj->w/2,  obj->h/2, -obj->d/2);
            glVertex3f( obj->w/2, -obj->h/2, -obj->d/2); glVertex3f( obj->w/2,  obj->h/2, -obj->d/2);
            glVertex3f( obj->w/2, -obj->h/2,  obj->d/2); glVertex3f( obj->w/2,  obj->h/2,  obj->d/2);
            glVertex3f(-obj->w/2, -obj->h/2,  obj->d/2); glVertex3f(-obj->w/2,  obj->h/2,  obj->d/2);
            
            glEnd();
            
            glPopMatrix();
            
            glLineWidth(1.0f); // Reset line width
            glDisable(GL_BLEND);
            glEnable(GL_LIGHTING);
            glColor3f(1, 1, 1); // Reset color
            break;
        }
    }
  }



float rayBoxIntersection(float rayStartX, float rayStartY, float rayStartZ,
    float rayDirX, float rayDirY, float rayDirZ,
    float boxMinX, float boxMinY, float boxMinZ,
    float boxMaxX, float boxMaxY, float boxMaxZ) {
  // Avoid division by zero
  if (fabs(rayDirX) < 1e-6) rayDirX = 1e-6;
  if (fabs(rayDirY) < 1e-6) rayDirY = 1e-6;
  if (fabs(rayDirZ) < 1e-6) rayDirZ = 1e-6;
  
  float tmin = (boxMinX - rayStartX) / rayDirX;
  float tmax = (boxMaxX - rayStartX) / rayDirX;
  
  if (tmin > tmax) { float temp = tmin; tmin = tmax; tmax = temp; }
  
  float tymin = (boxMinY - rayStartY) / rayDirY;
  float tymax = (boxMaxY - rayStartY) / rayDirY;
  
  if (tymin > tymax) { float temp = tymin; tymin = tymax; tymax = temp; }
  
  if ((tmin > tymax) || (tymin > tmax)) return -1;
  
  if (tymin > tmin) tmin = tymin;
  if (tymax < tmax) tmax = tymax;
  
  float tzmin = (boxMinZ - rayStartZ) / rayDirZ;
  float tzmax = (boxMaxZ - rayStartZ) / rayDirZ;
  
  if (tzmin > tzmax) { float temp = tzmin; tzmin = tzmax; tzmax = temp; }
  
  if ((tmin > tzmax) || (tzmin > tmax)) return -1;
  
  if (tzmin > tmin) tmin = tzmin;
  if (tzmax < tmax) tmax = tzmax;
  
  return tmin > 0 ? tmin : tmax;
  }
  
  
  int getObjectAtMouse(int mouseX, int mouseY) {
    // Get viewport dimensions
    GLint viewport[4];
    GLdouble modelMatrix[16], projMatrix[16];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
    
    // Convert mouse coordinates (flip Y)
    GLfloat winY = (float)viewport[3] - (float)mouseY;
    
    // Create ray from camera through mouse position
    GLdouble startX, startY, startZ;
    GLdouble endX, endY, endZ;
    
    // Near plane
    gluUnProject((GLdouble)mouseX, (GLdouble)winY, 0.0,
                modelMatrix, projMatrix, viewport,
                &startX, &startY, &startZ);
    
    // Far plane
    gluUnProject((GLdouble)mouseX, (GLdouble)winY, 1.0,
                modelMatrix, projMatrix, viewport,
                &endX, &endY, &endZ);
    
    // Ray direction
    float rayDirX = endX - startX;
    float rayDirY = endY - startY;
    float rayDirZ = endZ - startZ;
    
    // Normalize ray direction
    float rayLength = sqrt(rayDirX*rayDirX + rayDirY*rayDirY + rayDirZ*rayDirZ);
    if (rayLength > 0) {
        rayDirX /= rayLength;
        rayDirY /= rayLength;
        rayDirZ /= rayLength;
    }
    
    // Test intersection with each object
    float closestDistance = 1000.0f;
    int closestObject = -1;
    
    for (int i = 0; i < numSelectableObjects; i++) {
        Object* obj = &selectableObjects[i];
        
        // Simple bounding box intersection test
        float distance = rayBoxIntersection(
            startX, startY, startZ,
            rayDirX, rayDirY, rayDirZ,
            obj->x - obj->w/2, obj->y - obj->h/2, obj->z - obj->d/2,
            obj->x + obj->w/2, obj->y + obj->h/2, obj->z + obj->d/2
        );
        
        if (distance > 0 && distance < closestDistance) {
            closestDistance = distance;
            closestObject = obj->id;
        }
    }
    
    return closestObject;
  }
  
  void selectObject(int objectID) {
    // Deselect all objects first
    for (int i = 0; i < numSelectableObjects; i++) {
        selectableObjects[i].isSelected = 0;
    }
    
    selectedObjectID = objectID;
    // printf("Hi %d", selectedObjectID);
    
    if (objectID >= 0) {
        for (int i = 0; i < numSelectableObjects; i++) {
            if (selectableObjects[i].id == objectID) {
                selectableObjects[i].isSelected = 1;
                printf("Selected: %s\n", selectableObjects[i].name);
                break;
            }
        }
    }
  }
