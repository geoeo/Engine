#include "BoxGeometry.h"

BoxGeometry::BoxGeometry() {

  drawMode = GL_TRIANGLES;

  nVertices = 36;
  nColors = nNormals = nTangents = nBitangents = nUVs = nVertices;

  vertices = new vec3[nVertices];

  vertices[0] = vec3(-1.0f, 1.0f, -1.0f); // 4
  vertices[1] = vec3(-1.0f, -1.0f, -1.0f); // 3
  vertices[2] = vec3(1.0f, -1.0f, -1.0f); // 7
  vertices[3] = vec3(1.0f, -1.0f, -1.0f); // 8
  vertices[4] = vec3(1.0f, 1.0f, -1.0f); // 5
  vertices[5] = vec3(-1.0f, 1.0f, -1.0f); // 3

  vertices[6] = vec3(-1.0f, -1.0f, 1.0f); // 1
  vertices[7] = vec3(-1.0f, -1.0f, -1.0f); // 4
  vertices[8] = vec3(-1.0f, 1.0f, -1.0f); // 2
  vertices[9] = vec3(-1.0f, 1.0f, -1.0f); // 7
  vertices[10] = vec3(-1.0f, 1.0f, 1.0f); // 6
  vertices[11] = vec3(-1.0f, -1.0f, 1.0f); // 5

  vertices[12] = vec3(1.0f, -1.0f, -1.0f); // 1
  vertices[13] = vec3(1.0f, -1.0f, 1.0f); // 4
  vertices[14] = vec3(1.0f, 1.0f, 1.0f); // 2
  vertices[15] = vec3(1.0f, 1.0f, 1.0f); // 7
  vertices[16] = vec3(1.0f, 1.0f, -1.0f); // 6
  vertices[17] = vec3(1.0f, -1.0f, -1.0f); // 5

  vertices[18] = vec3(-1.0f, -1.0f, 1.0f); // 1
  vertices[19] = vec3(-1.0f, 1.0f, 1.0f); // 4
  vertices[20] = vec3(1.0f, 1.0f, 1.0f); // 2
  vertices[21] = vec3(1.0f, 1.0f, 1.0f); // 7
  vertices[22] = vec3(1.0f, -1.0f, 1.0f); // 6
  vertices[23] = vec3(-1.0f, -1.0f, 1.0f); // 5

  vertices[24] = vec3(-1.0f, 1.0f, -1.0f); // 1
  vertices[25] = vec3(1.0f, 1.0f, -1.0f); // 4
  vertices[26] = vec3(1.0f, 1.0f, 1.0f); // 2
  vertices[27] = vec3(1.0f, 1.0f, 1.0f); // 7
  vertices[28] = vec3(-1.0f, 1.0f, 1.0f); // 6
  vertices[29] = vec3(-1.0f, 1.0f, -1.0f); // 5

  vertices[30] = vec3(-1.0f, -1.0f, -1.0f); // 1
  vertices[31] = vec3(-1.0f, -1.0f, 1.0f); // 4
  vertices[32] = vec3(1.0f, -1.0f, -1.0f); // 2
  vertices[33] = vec3(1.0f, -1.0f, -1.0f); // 7
  vertices[34] = vec3(-1.0f, -1.0f, 1.0f); // 6
  vertices[35] = vec3(1.0f, -1.0f, 1.0f); // 5
}