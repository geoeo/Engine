#pragma once

#include "common.h"
#include "../threecpp/Scene.h"


class MainScene: public Scene {

public:
  int featureTextures = 1;
  int featureSteepTextures = 1;
  int featureShadows = 1;
  int featureSmoothShadows = 1;
  int featureReflection = 1;

  int debugSlope = 0;
  int debugDisplacement = 0;
  int debugVisibility = 0;
  int debugNormals = 0;
  int debugReflection = 0;

  MainScene();
  ~MainScene();

  void onKeyInput(const Event&);
  void setData(GLuint);
};