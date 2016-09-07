#pragma once

#include "common.h"

#include "SOIL.h"

class Material {

protected:
  void compileShaders();

public:
  // Program Id of compiled and linked shaders
  GLuint id;

  // Vertex Array Object
  GLuint vertexArrayObject;

  // Texture Object
  GLuint texture;

  Material(const char*, const char*, const char*);
  ~Material();

  virtual void setMVP(const mat4&, const mat4&, const mat4&, const mat4&);

  static GLuint loadTexture(const char*, bool isDepth = false, GLenum edge = GL_CLAMP_TO_EDGE);
};