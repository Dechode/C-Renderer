#include "obj_loader.h"
#include "glad/glad.h"
#include "io.h"
#include "math/linmath.h"
#include "max_values.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  void *items;
  size_t itemSize;
  size_t cap;
  size_t len;
} Array;

int arrayAppend(Array *arr, void *item) {
  if (arr->len == arr->cap) {
    arr->cap = (arr->cap > 0) ? arr->cap * 2 : 1;
    void *items = realloc((void *)arr->items, arr->itemSize * arr->cap);

    if (!items) {
      printf("Could not push back to array!\n");
      return -1;
    }
    arr->items = items;
  }
  size_t idx = arr->len++;
  memcpy((void *)arr->items + idx * arr->itemSize, item, arr->itemSize);
  return idx;
}

Mesh *loadObj(const char *path) {
  Mesh *mesh = (Mesh *)malloc(sizeof(Mesh));

  printf("\nLoading obj file: %s\n", path);

  FILE *fp;
  fp = fopen(path, "r");
  if (fp == NULL) {
    printf("Error loading obj from path %s", path);
    return NULL;
  }

  uint32_t objectCount = 0;
  uint32_t vertexCount = 0;
  uint32_t indexCount = 0;
  uint32_t uvCount = 0;
  uint32_t normalCount = 0;

  Array vertexIndices = {0};
  Array uvIndices = {0};
  Array normalIndices = {0};

  vertexIndices.itemSize = sizeof(uint32_t);
  uvIndices.itemSize = sizeof(uint32_t);
  normalIndices.itemSize = sizeof(uint32_t);

  vec3 tempVertices[MAX_VERTICES] = {0};
  vec2 tempUvs[MAX_VERTICES] = {0};
  vec3 tempNormals[MAX_VERTICES] = {0};

  uint32_t maxWordCount = 1000000;

  for (uint32_t i = 0; i < maxWordCount; i++) {
    char lineHeader[256];
    int res = fscanf(fp, "%s", lineHeader);
    if (res == EOF) {
      break;
    }
    if (strcmp(lineHeader, "o") == 0) {
      objectCount++;
    } else if (strcmp(lineHeader, "v") == 0) {
      vec3 vec = {0};
      fscanf(fp, "%f %f %f", &vec[0], &vec[1], &vec[2]);
      vec3_dup(tempVertices[vertexCount++], vec);
    } else if (strcmp(lineHeader, "vt") == 0) {
      vec2 uv = {0};
      fscanf(fp, "%f %f", &uv[0], &uv[1]);
      vec2_dup(tempUvs[uvCount++], uv);
    } else if (strcmp(lineHeader, "vn") == 0) {
      vec3 normal = {0};
      fscanf(fp, "%f %f %f", &normal[0], &normal[1], &normal[2]);
      vec3_dup(tempNormals[normalCount++], normal);
    } else if (strcmp(lineHeader, "f") == 0) {
      uint32_t vertexIndex[3] = {0};
      uint32_t uvIndex[3] = {0};
      uint32_t normalIndex[3] = {0};

      int matches = fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0],
                           &uvIndex[0], &normalIndex[0], &vertexIndex[1],
                           &uvIndex[1], &normalIndex[1], &vertexIndex[2],
                           &uvIndex[2], &normalIndex[2]);
      if (matches != 9) {
        printf("Could not find all 9 indices, found %d\n", matches);
        fclose(fp);
        return NULL;
      }

      indexCount++;

      arrayAppend(&vertexIndices, (void *)&vertexIndex[0]);
      arrayAppend(&vertexIndices, (void *)&vertexIndex[1]);
      arrayAppend(&vertexIndices, (void *)&vertexIndex[2]);
      arrayAppend(&uvIndices, (void *)&uvIndex[0]);
      arrayAppend(&uvIndices, (void *)&uvIndex[1]);
      arrayAppend(&uvIndices, (void *)&uvIndex[2]);
      arrayAppend(&normalIndices, (void *)&normalIndex[0]);
      arrayAppend(&normalIndices, (void *)&normalIndex[1]);
      arrayAppend(&normalIndices, (void *)&normalIndex[2]);
    }
  }

  fclose(fp);

  mesh->vertexCount = vertexIndices.len;
  mesh->indexCount = 0;

  Vertex *vertices =
      (Vertex *)malloc((size_t)mesh->vertexCount * sizeof(Vertex));

  for (uint32_t i = 0; i < vertexIndices.len; i++) {
    uint32_t vIdx = ((uint32_t *)vertexIndices.items)[i];
    uint32_t uIdx = ((uint32_t *)uvIndices.items)[i];
    uint32_t nIdx = ((uint32_t *)normalIndices.items)[i];

    vec3_dup(vertices[i].positions, tempVertices[vIdx - 1]);
    vec2_dup(vertices[i].uvs, tempUvs[uIdx - 1]);
    vec3_dup(vertices[i].normals, tempNormals[nIdx - 1]);
  }

  mesh->vertices = vertices;
  // mesh->indices = vertexIndices;

  printf("Object count = %d\n", objectCount);
  printf("Vertex count = %d\n", mesh->vertexCount);
  printf("Index count = %d\n", mesh->indexCount);

  return mesh;
}
