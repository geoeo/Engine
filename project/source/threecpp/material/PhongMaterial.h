#pragma once

#include "common.h"

#include "Material.h"

class PhongMaterial: public Material {

public:
  PhongMaterial(const char*, const char*, const char*);

  void setColor(vec3*);
  void setPhongReflection(vec3*, vec3*, vec3*, float);
};