#pragma once

#include "common.h"

#include "../threecpp/Model.h"
#include "../threecpp/Materials.h"
#include "../threecpp/Geometries.h"
#include "../threecpp/Cameras.h"
#include "../threecpp/Lights.h"

class ShadowMap : public Model {

public:
  BufferCamera* heightMapBuffer;
  Light* light;

  // Constructor
  ShadowMap(PerspectiveCamera*, Light*);

  // Destructor
  ~ShadowMap();

  void setData();
};