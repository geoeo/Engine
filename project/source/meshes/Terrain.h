#pragma once

#include "common.h"

#include "../threecpp/Model.h"
#include "../threecpp/Materials.h"
#include "../threecpp/Geometries.h"
#include "../threecpp/Cameras.h"

class Terrain : public Model {

private:
  GLuint snowTextureId;
  GLuint rockTextureId;
  GLuint landTextureId;
  GLuint woodTextureId;
  GLuint sandTextureId;

  const string SNOW = __DIR__ + string("textures/terrain/mountain.tga");
  const string ROCK = __DIR__ + string("textures/terrain/rock.tga");
  const string LAND = __DIR__ + string("textures/terrain/grass.tga");
  const string WOOD = __DIR__ + string("textures/terrain/forest.tga");
  const string SAND = __DIR__ + string("textures/terrain/sand.tga");

public:
  BufferCamera* heightMapBuffer;
  BufferCamera* shadowMapBuffer;

  // Constructor
  Terrain(PerspectiveCamera*);

  // Destructor
  ~Terrain();

  void setup();
  void setData();
};