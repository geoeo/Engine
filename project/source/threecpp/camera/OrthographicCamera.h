#pragma once

#include "common.h"
#include "Camera.h"


class OrthographicCamera: public Camera {

public:
  // Intrinsic Parameters
  float left;
  float right;
  float bottom;
  float top;
  float near;
  float far;

  // Constructor
  OrthographicCamera(float, float, float, float, float, float);

  // Destructor
  ~OrthographicCamera();

  OrthographicCamera* copy();

  void updateProjectionMatrix();
};