#include "Cloud.h"

Cloud::Cloud()
	: Model(new PlaneGeometry(), new BillboardMaterial((__DIR__ + string("textures/clouds_cropped.png")).data())) {
  // http://www.opengl-tutorial.org/intermediate-tutorials/billboards-particles/billboards/;
}

Cloud::~Cloud() {
	glDeleteTextures(1, meshes[0]->material->textures);
}