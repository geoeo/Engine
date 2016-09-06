#pragma once

#include "common.h"

#include "../threecpp/Model.h"
#include "../threecpp/Materials.h"
#include "../threecpp/Geometries.h"
#include "../threecpp/Cameras.h"

class Mirror : public Model {

private:

public:
  BufferCamera* reflection;

  // Constructor
  Mirror(PerspectiveCamera*);

  // Destructor
  ~Mirror();

  // void draw();
};