#pragma once

#include "common.h"
#include "Materials.h"
#include "Geometries.h"
#include "Mesh.h"

class Model : public Object {

public:
  vector<Mesh*> meshes;

  bool isTexture = false;

  // Constructor
  Model(Geometry*, Material*);
  Model(string pathToMesh);

  // Destructor
  ~Model();

  virtual void draw(GLuint frameBuffer = 0, float _time = 0, float _effect = 0);
  virtual void setData();
  void loadModel(string path);
  void processNode(aiNode* node, const aiScene* scene, vector<vec3>* verticies, vector<vec3>* normals, vector<vec3>* tangent,
	  vector <vec3>* biTangent, vector<vec2>* textureCoordiantes, vector<GLuint>* indices, Geometry* g);
  void generateGeometry(aiMesh* mesh, const aiScene* scene, vector<vec3>* verticies, vector<vec3>* normals, vector<vec3>* tangent,
	  vector <vec3>* biTangent, vector<vec2>* textureCoordiantes, vector<GLuint>* indices, Geometry* g);
 
};