#include "ShadowMap.h"

#include "_terrain_shadow_vshader.h"
#include "_terrain_shadow_fshader.h"

ShadowMap::ShadowMap(PerspectiveCamera* camera, Light* _light)
	: Model(new PlaneVert(), new StaticMaterial(_terrain_shadow_vshader, _terrain_shadow_fshader, NULL)) {

  light = _light;

}

ShadowMap::~ShadowMap() {

}

void ShadowMap::setData(){
  GLuint program = meshes[0]->material->id;
  glUseProgram(program);

  //// Bind the material as texture
  //glActiveTexture(GL_TEXTURE0);
  //glBindTexture(GL_TEXTURE_2D, heightMapBuffer->texture);

  //// Link material texture attribute
  //glUniform1i(glGetUniformLocation(program, "heightMap"), 0);

  GLuint lightMvpID = glGetUniformLocation(program, "lightMVP");
  glUniformMatrix4fv(lightMvpID, ONE, DONT_TRANSPOSE, light->getMVP().data());

  glUseProgram(CLEAR);
}