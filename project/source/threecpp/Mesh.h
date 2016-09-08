#pragma once

#include "common.h"
#include "Object.h"
#include "Materials.h"
#include "Geometries.h"

class Mesh : public Object {

private:
	bool shouldSetDataVal;

protected:
  void setup();

public:
  Geometry* geometry;
  Material* material;


  // Constructor
  Mesh(Geometry*, Material*, bool _shouldSetData = false);
//  Model(string pathToMesh);

  // Destructor
  ~Mesh();

  virtual void draw(GLuint frameBuffer = 0, float _time = 0, float _effect = 0);
  virtual void setData();
  void setImportedTextures();
  bool shouldSetData(){ return shouldSetDataVal; }
 
};