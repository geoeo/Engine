#pragma once

#include "common.h"
#include "Materials.h"
#include "Geometries.h"
#include "Mesh.h"

class Model : public Object {

private:

	bool shouldSetDataVal;

public:
  vector<Mesh*> meshes;

  bool isTexture = false;

  // Constructor
  Model(Geometry*, Material*, bool _shouldSetData = true);
  Model(string pathToMesh, bool _shouldSetData= false);

  // Destructor
  ~Model();

  virtual void draw(GLuint frameBuffer = 0, float _time = 0, float _effect = 0);
  virtual void setData();
  void loadModel(string path);
  void processNode(aiNode* node, const aiScene* scene);
  Mesh* generateMesh(aiMesh* mesh, const aiScene* scene);
  bool shouldSetData(){ return shouldSetDataVal; }
 
};