#pragma once

#include "Geometry.h"

class Surface : public Geometry {

private:
  float lb;
  float rt;

  unsigned int nRows;
  unsigned int nCols;

public:

  // Constructor
  Surface(unsigned int);
  void load();
};