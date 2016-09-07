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

	Material * mat = meshes[0]->material;
  snowTextureId = mat->loadTexture(SNOW.data(), false, GL_REPEAT);
  rockTextureId = mat->loadTexture(ROCK.data(), false, GL_REPEAT);
  landTextureId = mat->loadTexture(LAND.data(), false, GL_REPEAT);
  woodTextureId = mat->loadTexture(WOOD.data(), false, GL_REPEAT);
  sandTextureId = mat->loadTexture(SAND.data(), false, GL_REPEAT);

  ((PhongMaterial*)mat)->setPhongReflection(
    new vec3(0.5, 0.5, 0.5),  // ambient
	new vec3(0.05, 0.05, 0.05),  // diffuse
    new vec3(0.3, 0.3, 0.3),  // specular
    2.0f                     // shininess
  );
}

void Terrain::setData(){

	GLuint program = meshes[0]->material->id;
  glUseProgram(program);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, heightMapBuffer->texture);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(program, "heightMap"), 0);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0 + 1);
  glBindTexture(GL_TEXTURE_2D, snowTextureId);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(program, "snowTexture"), 1);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0 + 2);
  glBindTexture(GL_TEXTURE_2D, landTextureId);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(program, "landTexture"), 2);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0 + 3);
  glBindTexture(GL_TEXTURE_2D, woodTextureId);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(program, "woodTexture"), 3);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0 + 4);
  glBindTexture(GL_TEXTURE_2D, rockTextureId);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(program, "rockTexture"), 4);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0 + 5);
  glBindTexture(GL_TEXTURE_2D, sandTextureId);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(program, "sandTexture"), 5);

  // Bind shadow map as texture
  glActiveTexture(GL_TEXTURE0 + 6);
  glBindTexture(GL_TEXTURE_2D, shadowMapBuffer->texture);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(program, "shadowMap"), 6);

  glUseProgram(CLEAR);
}
