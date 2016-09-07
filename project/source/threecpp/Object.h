#pragma once

#include "common.h"

class Object {

private:

protected:
  void updateModelMatrix();

  mat4 _scale = mat4::Identity();
  mat4 _rotation = mat4::Identity();
  mat4 _translation = mat4::Identity();

public:
  void rotate(float, vec3);
  void rotateX(float);
  void rotateY(float);
  void rotateZ(float);
  void scale(float);
  void scale(float,float,float);
  void translate(float, float, float);
  void resetScale();
  void resetTranslation();
  void resetRotation();

  mat4 model = mat4::Identity();
  virtual~ Object();
};