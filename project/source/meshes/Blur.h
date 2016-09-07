#pragma once

#include "common.h"

#include "../threecpp/Model.h"
#include "../threecpp/Materials.h"
#include "../threecpp/Geometries.h"
#include "camera/BufferCamera.h"


class Blur : public Model {

private:
public:
  GLuint blurFBO[2];
  GLuint blurColorbuffers[2];
  BufferCamera * _sceneCamera;
  GLboolean horizontal;

  // Constructor
  Blur(BufferCamera*);

  // Destructor
  ~Blur();

  void draw(GLuint frameBuffer = 0, float _time = 0, float _effect = 0);
  void setup(Camera*, GLsizei, GLsizei);
  void setData(){};
};