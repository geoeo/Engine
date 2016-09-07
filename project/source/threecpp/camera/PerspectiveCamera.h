#pragma once

#include "common.h"
#include "Camera.h"


class PerspectiveCamera: public Camera {

public:
  // Intrinsic Parameters
  float fieldOfView;
  float aspectRatio;
  float nearPlane;
  float farPlane;

  // Constructor
  PerspectiveCamera(float, float, float, float,bool);

  // Destructor
  ~PerspectiveCamera();

  void onResize(const Event&);

  PerspectiveCamera* copy();

  void updateProjectionMatrix();
};