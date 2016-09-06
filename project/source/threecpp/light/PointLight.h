#pragma once

#include "common.h"
#include "Light.h"


class PointLight: public Light {

public:
  PointLight(const char*);
  ~PointLight();
};