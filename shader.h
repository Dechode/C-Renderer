#pragma once

#include "glad/glad.h"
#include "linmath.h"
#include "max_values.h"
#include <stdint.h>

typedef struct {
  uint32_t id;
  char fragPath[MAX_PATH_CHARS];
  char vertPath[MAX_PATH_CHARS];
} Shader;

Shader createShader(const char *pathFrag, const char *pathVert);

void bindShader(GLuint shaderID);
void unBindShader(void);

void setInt(Shader *shader, const char *name, int value);
void setIntArray(Shader *shader, const char *name, int values[], uint32_t count);
void setFloat(Shader *shader, const char *name, float value);
void setFloat2(Shader *shader, const char *name, vec2 value);
void setFloat3(Shader *shader, const char *name, vec3 value);
void setFloat4(Shader *shader, const char *name, vec4 value);
void setMat4(Shader *shader, const char *name, mat4x4 value);

