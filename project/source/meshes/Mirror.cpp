#include "Mirror.h"

#include "_buffer_fshader.h"
#include "_texture_vshader.h"

Mirror::Mirror(PerspectiveCamera* camera)
	: Model(new PlaneGeometry(), new Material(_texture_vshader, _buffer_fshader, NULL)) {

  reflection = BufferCamera::fromCamera(camera,false);
  reflection->createFrameBuffer(1024, 768);
  meshes[0]->material->textures[Material::DIFFUSE_TEXTURE_INDEX] = reflection->texture;
  isTexture = true;
}

Mirror::~Mirror() {
  glDeleteTextures(1, &(reflection->texture));
}