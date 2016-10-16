#pragma once

#include "common.h"
#include "Materials.h"
#include "Geometries.h"
#include "Mesh.h"

#include "_simple_fshader.h"
#include "_simple_vshader.h"
#include "_texture_2d_fshader.h"

class Model : public Object {

private:

	bool shouldSetDataVal;
	Model* Copy();
	Model(bool _shouldSetDataVal);

public:

  Model* copyForShadowMapping = NULL;

  vector<Mesh*> meshes;
  bool isTexture = false;

  // Constructor
  Model(Geometry*, Material*, bool _shouldSetData = true, bool createShadowMapCopy = false);
  Model(string pathToMesh, bool _shouldSetData= false);

  // Destructor
  ~Model();

  virtual void draw(GLuint frameBuffer = 0, float _time = 0, float _effect = 0);
  virtual void setData();
  void loadModel(string path);
  void processNode(aiNode* node, const aiScene* scene);
  Mesh* generateMesh(aiMesh* mesh, const aiScene* scene, bool forShadowMapping = false);
  bool shouldSetData(){ return shouldSetDataVal; }
  Model* returnCopyForShadowMapping(); // returns a copy of the model without any of the textures.
 
};