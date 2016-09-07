#pragma once

#include "common.h"
#include "Light.h"


class DirectedLight: public Light, public OrthographicCamera {

public:
  DirectedLight(const char*);
  ~DirectedLight();
};