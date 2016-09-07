#pragma once

#include "common.h"
#include "Object.h"
#include "Cameras.h"


class Light: public Object {

protected:
  const char* descriptor;

public:
  vec3 Ia = vec3(1.0f, 1.0f, 1.0f);
  vec3 Id = vec3(1.0f, 1.0f, 1.0f);
  vec3 Is = vec3(1.0f, 1.0f, 1.0f);

  vec3 lookAt;
  vec3 up;
  vec3 position;

  mat4 projection;

  // translate light-coordinates (-1,-1)x(1,1) to texture coordinates(0,0)x(1,1)
  mat4 offsetMatrix = mat4::Identity();

  Light(const char*);
  ~Light();

  virtual void setData(GLuint);
  virtual mat4 getMVP();
};