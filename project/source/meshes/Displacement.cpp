#include "Displacement.h"

#include "_heightmap_vshader.h"
#include "_heightmap_fshader.h"

Displacement::Displacement()
	: Model(new PlaneVert(), new StaticMaterial(_heightmap_vshader, _heightmap_fshader, NULL)) {
}

Displacement::~Displacement() {
	glDeleteTextures(1, meshes[0]->material->textures);
}