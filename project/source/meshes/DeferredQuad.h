#pragma once

#include "common.h"

#include "../threecpp/Model.h"
#include "../threecpp/Materials.h"
#include "../threecpp/Geometries.h"
#include "camera/BufferCamera.h"


class DeferredQuad : public Model {

private:
public:
  BufferCamera * _gBufferCamera;

  // Constructor
  DeferredQuad(BufferCamera*);

  // Destructor
  ~DeferredQuad();

  void draw(GLuint frameBuffer = 0, float _time = 0, float _effect = 0);
  void setup(Camera*, GLsizei, GLsizei);
  void setData();
};