#pragma once

#include "common.h"

#include "Material.h"

class StaticMaterial: public Material {

public:
  StaticMaterial(const char*, const char*, const char*);
  void setMVP(const mat4&, const mat4&, const mat4&, const mat4&);
};