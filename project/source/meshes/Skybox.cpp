#include "Skybox.h"

#include "_texture_vshader.h"
#include "_texture_3d_fshader.h"

#include "_simple_fshader.h"
#include "_simple_vshader.h"

Skybox::Skybox()
	: Model(new BoxIndicesGeometry(), new Material(_texture_vshader, _texture_3d_fshader, NULL)) {

  setup();
}

void Skybox::setup(){
  // TODO: We need to refactor this, it's not DRY
  glUseProgram(material->id);

  glGenVertexArrays(1, &(material->vertexArrayObject));
  glBindVertexArray(material->vertexArrayObject);

  checkGLErrors("SKYBOX_MATERIAL::CompileAndLinkShaders", "AFTER vertexArrayObject");

  // buffer that holds the vertex data of the geometry object
  GLuint vertexBufferObject;

  glGenBuffers(1, &vertexBufferObject);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

  glBufferData(GL_ARRAY_BUFFER, geometry->getNumVertices() * sizeof(vec3), geometry->getVertices(), GL_STATIC_DRAW);

  if (geometry->getNumIndices() > 0){

	  GLuint elementBufferObject;

	  glGenBuffers(ONE, &elementBufferObject);
	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	  glBufferData(GL_ELEMENT_ARRAY_BUFFER, geometry->getNumIndices() * sizeof(GLuint),
		  geometry->getIndices(), GL_STATIC_DRAW);

	  checkGLErrors("MATERIAL::CompileShaders", "AFTER elementBufferObject");
  }

  glVertexAttribPointer(0, 3, GL_FLOAT, DONT_NORMALIZE, ZERO_STRIDE, ZERO_BUFFER_OFFSET);
  glEnableVertexAttribArray(0);

  checkGLErrors("SKYBOX_MATERIAL::CompileAndLinkShaders", "AFTER vertexBufferObject");

  // Cube Map - Loads textures
  createCubeMap(FRONT.data(), BACK.data(), TOP.data(), BOTTOM.data(), LEFT.data(), RIGHT.data());

  checkGLErrors("SKYBOX_MATERIAL::CompileAndLinkShaders", "AFTER CUBEMAP");

  // Clean up
  glBindBuffer(GL_ARRAY_BUFFER, CLEAR);
  glBindVertexArray(CLEAR);
  glUseProgram(CLEAR);

  checkGLErrors("SKYBOX_MATERIAL::CompileAndLinkShaders", "END");
}

void Skybox::draw(GLuint frameBuffer, float _time, float _effect){
	glDepthMask(GL_FALSE);
	glUseProgram(material->id);

	glUniform1f(glGetUniformLocation(material->id, "time"), _time);

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glBindVertexArray(material->vertexArrayObject);

	if (geometry->getNumIndices() > 0)
		glDrawElements(geometry->getDrawMode(), geometry->getNumIndices(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(geometry->getDrawMode(), 0, geometry->getNumVertices());

	glBindVertexArray(CLEAR);
	glUseProgram(CLEAR);

	glBindTexture(GL_TEXTURE_2D, CLEAR);
	glBindFramebuffer(GL_FRAMEBUFFER, CLEAR);
	glDepthMask(GL_TRUE);

}

// @src: http://www.antongerdelan.net/opengl/cubemaps.html
void Skybox::createCubeMap(const char* front, const char* back, const char* top, const char*bottom, const char* left, const char*right){

  glGenTextures(ONE, &(material->texture));

  loadCubeMapSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
  loadCubeMapSide(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
  loadCubeMapSide(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
  loadCubeMapSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
  loadCubeMapSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
  loadCubeMapSide(GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  checkGLErrors("SKYBOX_MATERIAL::CreateCubeMap", "END");
}

void Skybox::loadCubeMapSide(GLenum side_target, const char* fileName){

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, material->texture);

  int width, height, n;

  unsigned char*  image_data = SOIL_load_image(fileName, &width, &height, &n, SOIL_LOAD_RGBA);

  glTexImage2D(side_target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

  SOIL_free_image_data(image_data);
}

Skybox::~Skybox(){
  // glDeleteTextures(1, &(material->texture));
}

void Skybox::setData(){
  glUseProgram(material->id);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, material->texture);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(material->id, "cubeSampler"), 0);

  //glBindTexture(GL_TEXTURE_CUBE_MAP, CLEAR);
  glUseProgram(CLEAR);
}