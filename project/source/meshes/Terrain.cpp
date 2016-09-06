#include "Terrain.h"

#include "_terrain_fshader.h"
#include "_terrain_vshader.h"

Terrain::Terrain(PerspectiveCamera* camera)
	: Model(new Surface(4096), new PhongMaterial(_terrain_vshader, _terrain_fshader, NULL)) {

  heightMapBuffer = BufferCamera::fromCamera(camera,false);
  heightMapBuffer->createFrameBuffer(1024, 768);

  shadowMapBuffer = BufferCamera::fromCamera(camera,false);
  shadowMapBuffer->createFrameBuffer(1024, 768, true);

  setup();
}

Terrain::~Terrain() {
  glDeleteTextures(1, &(heightMapBuffer->texture));
}

void Terrain::setup(){
  snowTextureId = material->loadTexture(SNOW.data(), false, GL_REPEAT);
  rockTextureId = material->loadTexture(ROCK.data(), false, GL_REPEAT);
  landTextureId = material->loadTexture(LAND.data(), false, GL_REPEAT);
  woodTextureId = material->loadTexture(WOOD.data(), false, GL_REPEAT);
  sandTextureId = material->loadTexture(SAND.data(), false, GL_REPEAT);

  ((PhongMaterial*)material)->setPhongReflection(
    new vec3(0.5, 0.5, 0.5),  // ambient
	new vec3(0.05, 0.05, 0.05),  // diffuse
    new vec3(0.3, 0.3, 0.3),  // specular
    2.0f                     // shininess
  );
}

void Terrain::setData(){
  glUseProgram(material->id);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, heightMapBuffer->texture);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(material->id, "heightMap"), 0);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0 + 1);
  glBindTexture(GL_TEXTURE_2D, snowTextureId);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(material->id, "snowTexture"), 1);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0 + 2);
  glBindTexture(GL_TEXTURE_2D, landTextureId);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(material->id, "landTexture"), 2);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0 + 3);
  glBindTexture(GL_TEXTURE_2D, woodTextureId);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(material->id, "woodTexture"), 3);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0 + 4);
  glBindTexture(GL_TEXTURE_2D, rockTextureId);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(material->id, "rockTexture"), 4);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0 + 5);
  glBindTexture(GL_TEXTURE_2D, sandTextureId);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(material->id, "sandTexture"), 5);

  // Bind shadow map as texture
  glActiveTexture(GL_TEXTURE0 + 6);
  glBindTexture(GL_TEXTURE_2D, shadowMapBuffer->texture);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(material->id, "shadowMap"), 6);

  glUseProgram(CLEAR);
}
