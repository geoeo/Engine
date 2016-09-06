#pragma once

#include "common.h"

#include "../threecpp/Mesh.h"
#include "../threecpp/Materials.h"
#include "../threecpp/Geometries.h"
#include "camera/BufferCamera.h"
#include "Blur.h"


class Bloom : public Model {

private:
public:
  
  Blur * _blurMesh;
  BufferCamera * _sceneCamera;

  // Constructor
  Bloom(BufferCamera*, Blur*);

  // Destructor
  ~Bloom();

  void draw(GLuint frameBuffer = 0, float _time = 0, float _effect = 0);
  void setup(Camera*, GLsizei, GLsizei);
  void setData(){};
};