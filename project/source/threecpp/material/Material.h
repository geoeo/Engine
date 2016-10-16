#pragma once

#include "common.h"
#include "SOIL.h"
#include "_shadow_fshader.h"
#include "_shadow_vshader.h"

class Material {

private:

	static const int NUMBER_OF_SUPPORTED_TEXTURES = 3;

	void rebindShaders(const char* vertexShader, const char* fragmentShader, const char* geometryShader);

protected:
	void compileShaders(const char*, const char*, const char*);

public:

  static const int DIFFUSE_TEXTURE_INDEX = 0;
  static const int SPECULAR_TEXTURE_INDEX = 1;
  static const int NORMAL_TEXTURE_INDEX = 2;

  // Program Id of compiled and linked shaders
  GLuint id;

  // Vertex Array Object
  GLuint vertexArrayObject;

  // Texture Object
  // 0 - diffuse, 1 - specular, 2 - normal
  GLuint* textures;

  Material(const char*, const char*, const char*);
  ~Material();

  virtual void setMVP(const mat4&, const mat4&, const mat4&, const mat4&);

  static GLuint loadTexture(const char*, bool isDepth = false, GLenum edge = GL_CLAMP_TO_EDGE);

  void bindShadowMappingShaders();

};