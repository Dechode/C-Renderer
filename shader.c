#include "shader.h"
#include "glad/glad.h"
#include "io.h"
#include <stdio.h>
#include <string.h>

Shader createShader(const char *pathFrag, const char *pathVert) {
  int success = 0;
  char log[512];

  File fileVertex = ioReadFile(pathVert);
  if (!fileVertex.isValid) {
    printf("Error reading vertex shader: %s\n", pathVert);
    exit(EXIT_FAILURE);
  }

  uint32_t shaderVertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shaderVertex, 1, (const char *const *)&fileVertex, NULL);
  glCompileShader(shaderVertex);
  glGetShaderiv(shaderVertex, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shaderVertex, 512, NULL, log);
    printf("Error compiling vertex shader: %s\n", log);
    exit(EXIT_FAILURE);
  }

  File fileFragment = ioReadFile(pathFrag);
  if (!fileFragment.isValid) {
    printf("Error reading fragment shader: %s\n", pathFrag);
    exit(EXIT_FAILURE);
  }

  uint32_t shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shaderFragment, 1, (const char *const *)&fileFragment, NULL);
  glCompileShader(shaderFragment);
  glGetShaderiv(shaderFragment, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shaderFragment, 512, NULL, log);
    printf("Error compiling fragment shader: %s\n", log);
    exit(EXIT_FAILURE);
  }

  Shader shader = {0};
  strcpy(shader.fragPath, pathFrag);

  uint32_t shaderID = glCreateProgram();
  glAttachShader(shaderID, shaderVertex);
  glAttachShader(shaderID, shaderFragment);
  glLinkProgram(shaderID);
  glGetProgramiv(shaderID, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(shaderID, 512, NULL, log);
    printf("Error linking shader: %s\n", log);
    exit(EXIT_FAILURE);
  }
  shader.id = shaderID;

  free(fileVertex.data);
  free(fileFragment.data);

  return shader;
}

void bindShader(GLuint shaderID) { glUseProgram(shaderID); }

void unBindShader(void) { glUseProgram(0); }

void setInt(Shader *shader, const char *name, int value) {
  GLint loc = glGetUniformLocation(shader->id, name);
  glUniform1i(loc, value);
}

void setIntArray(Shader *shader, const char *name, int values[],
                 uint32_t count) {
  GLint loc = glGetUniformLocation(shader->id, name);
  glUniform1iv(loc, count, values);
}

void setFloat(Shader *shader, const char *name, float value) {
  GLint loc = glGetUniformLocation(shader->id, name);
  glUniform1f(loc, value);
}

void setFloat2(Shader *shader, const char *name, vec2 value) {
  GLint loc = glGetUniformLocation(shader->id, name);
  glUniform2f(loc, value[0], value[1]);
}

void setFloat3(Shader *shader, const char *name, vec3 value) {
  GLint loc = glGetUniformLocation(shader->id, name);
  glUniform3f(loc, value[0], value[1], value[2]);
}

void setFloat4(Shader *shader, const char *name, vec4 value) {
  GLint loc = glGetUniformLocation(shader->id, name);
  glUniform4f(loc, value[0], value[1], value[2], value[3]);
}

void setMat4(Shader *shader, const char *name, mat4x4 value) {
  GLint loc = glGetUniformLocation(shader->id, name);
  glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
}
