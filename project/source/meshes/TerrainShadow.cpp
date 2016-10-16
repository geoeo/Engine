#include "TerrainShadow.h"

#include "_terrain_shadow_vshader.h"
#include "_terrain_shadow_fshader.h"

TerrainShadow::TerrainShadow(PerspectiveCamera* camera, Light* _light)
	: Model(new Surface(4096), new StaticMaterial(_terrain_shadow_vshader, _terrain_shadow_fshader, NULL)) {

  light = _light;

  heightMapBuffer = BufferCamera::fromCamera(camera,false);
  heightMapBuffer->createFrameBuffer(1024, 768);
}

TerrainShadow::~TerrainShadow() {
  glDeleteTextures(1, &(heightMapBuffer->texture));
}

void TerrainShadow::setData(){
  GLuint program = meshes[0]->material->id;
  glUseProgram(program);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, heightMapBuffer->texture);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(program, "heightMap"), 0);

  glUseProgram(CLEAR);
}