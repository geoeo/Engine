#pragma once

#include "common.h"
#include "SOIL.h"

#include "../threecpp/Model.h"
#include "../threecpp/Materials.h"
#include "../threecpp/Geometries.h"

class Skybox : public Model {

private:
  void loadCubeMapSide(GLenum sideTarget, const char * fileName);
  void createCubeMap(const char* front, const char* back, const char* top, const char*bottom, const char* left, const char*right);

  const string FRONT = __DIR__ + string("textures/skybox/front.jpg");
  const string BACK = __DIR__ + string("textures/skybox/back.jpg");
  const string TOP = __DIR__ + string("textures/skybox/top.jpg");
  const string BOTTOM = __DIR__ + string("textures/skybox/bottom.jpg");
  const string LEFT = __DIR__ + string("textures/skybox/left.jpg");
  const string RIGHT = __DIR__ + string("textures/skybox/right.jpg");

protected:
  void setup();

public:
  // Constructor
  Skybox();
  // Destructor
  ~Skybox();

  void setData();
  void draw(GLuint frameBuffer, float _time, float _effect = 0);
};