#pragma once

#include "linmath.h"
#include "mesh.h"
#include "glad/glad.h"


static GLfloat cubeVertexPositions[] = {
    // front
    -1.0, -1.0,  1.0,
     1.0, -1.0,  1.0,
     1.0,  1.0,  1.0,
    -1.0,  1.0,  1.0,
    // back
    -1.0, -1.0, -1.0,
     1.0, -1.0, -1.0,
     1.0,  1.0, -1.0,
    -1.0,  1.0, -1.0
};

void initCube(void);
void drawCube(vec3 position, float rotation, vec3 size, vec4 color);
// float *getCubeVertices(void);