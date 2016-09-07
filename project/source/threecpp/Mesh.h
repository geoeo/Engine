#pragma once

#include "common.h"
#include "Object.h"
#include "Materials.h"
#include "Geometries.h"

class Mesh : public Object {

protected:
  void setup();

public:
  Geometry* geometry;
  Material* material;


  // Constructor
  Mesh(Geometry*, Material*);
//  Model(string pathToMesh);

  // Destructor
  ~Mesh();

  virtual void draw(GLuint frameBuffer = 0, float _time = 0, float _effect = 0);
  virtual void setData();
//  void loadModel(string path);
//  void processNode(aiNode* node, const aiScene* scene, vector<vec3>* verticies, vector<vec3>* normals, vector<vec3>* tangent,
//	  vector <vec3>* biTangent, vector<vec2>* textureCoordiantes, vector<GLuint>* indices, Geometry* g);
//  void generateGeometry(aiMesh* mesh, const aiScene* scene, vector<vec3>* verticies, vector<vec3>* normals, vector<vec3>* tangent,
//	  vector <vec3>* biTangent, vector<vec2>* textureCoordiantes, vector<GLuint>* indices, Geometry* g);
// 
};