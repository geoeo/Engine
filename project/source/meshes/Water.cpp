#include "Water.h"

#include "_water_fshader.h"
#include "_water_vshader.h"


Water::Water(PerspectiveCamera* camera, Skybox* _sky)
	: Model(new Surface(2048), new PhongMaterial(_water_vshader, _water_fshader, NULL)) {

  shadowMapBuffer = BufferCamera::fromCamera(camera,false);
  shadowMapBuffer->createFrameBuffer(1024, 768, true);

  sky = _sky;

  setup();
}

Water::~Water() {
  glDeleteTextures(1, &(material->texture));
}

void Water::setup() {

  material->texture = Material::loadTexture(WAVEMAP.data(), false, GL_REPEAT);

  ((PhongMaterial*)material)->setPhongReflection(
    new vec3(0.4, 0.4, 0.4),  // ambient
    new vec3(0.3, 0.3,0.3),  // diffuse
    new vec3(1.8, 1.8, 1.8),  // specular
    10.0f                     // shininess
  );

  ((PhongMaterial*)material)->setColor(
    new vec3(0.0, 0.0, 1.0) // blue
  );
}

void Water::setData() {
  glUseProgram(material->id);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, material->texture);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(material->id, "waveMap"), 0);

  // Bind shadow map as texture
  glActiveTexture(GL_TEXTURE0 + 1);
  glBindTexture(GL_TEXTURE_2D, shadowMapBuffer->texture);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(material->id, "shadowMap"), 1);

  // Bind shadow map as texture
  glActiveTexture(GL_TEXTURE0 + 2);
  glBindTexture(GL_TEXTURE_CUBE_MAP, sky->material->texture);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(material->id, "cubeSampler"), 2);
}