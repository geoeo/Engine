#include "StripBoxGeometry.h"

StripBoxGeometry::StripBoxGeometry() {

  drawMode = GL_TRIANGLE_STRIP;

  nVertices = 14;
  nColors = nNormals = nTangents = nBitangents = nUVs = nVertices;

  vertices = new vec3[nVertices];
  colors = new vec3[nVertices];

  vertices[0] = vec3(1, 0, 0); // 4
  vertices[1] = vec3(0, 0, 0); // 3
  vertices[2] = vec3(1, 0, -1); // 7
  vertices[3] = vec3(0, 0, -1); // 8

  vertices[4] = vec3(0, 1, -1); // 5
  vertices[5] = vec3(0, 0, 0); // 3
  vertices[6] = vec3(0, 1, 0); // 1
  vertices[7] = vec3(1, 0, 0); // 4

  vertices[8] = vec3(1, 1, 0); // 2
  vertices[9] = vec3(1, 0, -1); // 7
  vertices[10] = vec3(1,1, -1); // 6
  vertices[11] = vec3(0, 1, -1); // 5

  vertices[12] = vec3(1,1, 0); // 2
  vertices[13] = vec3(0, 1, 0); // 1


  colors[0] = vec3(1, 0, 0);
  colors[1] = vec3(0, 1, 0);
  colors[2] = vec3(0, 0, 1);
  colors[3] = vec3(1, 0, 0);

  colors[4] = vec3(0, 1, 0);
  colors[5] = vec3(0, 1, 0);
  colors[6] = vec3(0, 0, 1);
  colors[7] = vec3(1, 0, 0);

  colors[8] = vec3(0, 1, 0);
  colors[9] = vec3(0, 0, 1);
  colors[10] = vec3(0, 1, 0);
  colors[11] = vec3(1, 0, 0);

  colors[12] = vec3(0, 1, 0);
  colors[13] = vec3(0, 0, 1);
}