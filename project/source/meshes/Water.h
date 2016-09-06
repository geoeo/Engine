#pragma once

#include "common.h"

#include "../threecpp/Mesh.h"
#include "../threecpp/Materials.h"
#include "../threecpp/Geometries.h"
#include "../threecpp/Cameras.h"
#include "Skybox.h"

class Water : public Model {

private:

public:
  BufferCamera* shadowMapBuffer;
  Skybox* sky;

  // Constructor
  Water(PerspectiveCamera*, Skybox*);

  const string WAVEMAP = __DIR__ + string("textures/water/wavemap.tga");

  // Destructor
  ~Water();

  void setData();
  void setup();
};