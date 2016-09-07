#pragma once

#include "common.h"

#include "../threecpp/Model.h"
#include "../threecpp/Materials.h"
#include "../threecpp/Geometries.h"
#include "../threecpp/Cameras.h"
#include "../threecpp/Lights.h"

class TerrainShadow : public Model {

public:
  BufferCamera* heightMapBuffer;
  Light* light;

  // Constructor
  TerrainShadow(PerspectiveCamera*, Light*);

  // Destructor
  ~TerrainShadow();

  void setData();
};