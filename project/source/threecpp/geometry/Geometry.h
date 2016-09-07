#pragma once

#include "common.h"

class Geometry { // Refactor Geometry to use structs

protected:

  // Array of Vertices
  vec3* vertices;

  //Array of indicies
  vector<GLuint> indices;

  // Color data of the vertecies
  vec3* colors;

  // normals of the vertecies
  vec3* normals;

  // tanget of the vertecies
  vec3* tangent;

  // bitanget of the vertecies
  vec3* bitangent;

  // texture coordiantes of the vertecies
  vec2* UVs;

  // child geometries e.g. when loading external meshes
  Geometry *children;

  // Draw mode
  GLenum drawMode;

  // Number of Vertices
  unsigned int nVertices;
  // Number of colors
  unsigned int nColors;
  // Number of normals
  unsigned int nNormals;
  // Number of tangents
  unsigned int nTangents;
  // Number of bitangents
  unsigned int nBitangents;
  // Number of UVs
  unsigned int nUVs;

  // Model Matrix
  mat4 model;

public:
  GLenum getDrawMode(void) { return drawMode; }
  vec3* getVertices(void) { return vertices; }
  vec3* getColors(void) { return colors; }
  vec3* getNormals(void) { return normals; }
  vec3* getTangent(void) { return tangent; }
  vec3* getBitangent(void) { return bitangent; }
  GLuint* getIndices(void) { return &indices[0]; }
  Geometry* getChildren(void) { return children; }
  vec2* getUVs(void) { return UVs; }
  unsigned int getNumVertices(void) { return nVertices; }
  unsigned int getNumNormals(void) { return nNormals; }
  unsigned int getNumUVs(void) { return nUVs; }
  unsigned int getNumIndices(void) { return indices.size(); }
  unsigned int getNumColors(void) { return nColors; }
  unsigned int getNumTangent(void) { return nTangents; }
  unsigned int getNumBitangent(void) { return nBitangents; }
  mat4 getModelMatrix(){ return model; }

  // Constructor
  Geometry();
  Geometry(vector<vec3> verticesIn, vector<vec3> normalsIn, vector<vec3> tangentsIn, vector<vec3> biTangentsIn, vector<vec2> textureCoordiantesIn, vector<GLuint> indicesIn);

  // Destructor
  virtual ~Geometry();
};