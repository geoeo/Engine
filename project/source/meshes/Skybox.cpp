#include "Skybox.h"

#include "_texture_vshader.h"
#include "_texture_3d_fshader.h"

Skybox::Skybox()
	: Model(new BoxIndicesGeometry(), new Material(_texture_vshader, _texture_3d_fshader, NULL)) {

  setup();
}

void Skybox::setup(){

	Material* mat = meshes[0]->material;
	Geometry* geo = meshes[0]->geometry;
  // TODO: We need to refactor this, it's not DRY
  glUseProgram(mat->id);

  glGenVertexArrays(1, &(mat->vertexArrayObject));
  glBindVertexArray(mat->vertexArrayObject);

  checkGLErrors("SKYBOX_MATERIAL::CompileAndLinkShaders", "AFTER vertexArrayObject");

  // buffer that holds the vertex data of the geometry object
  GLuint vertexBufferObject;

  glGenBuffers(1, &vertexBufferObject);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

  glBufferData(GL_ARRAY_BUFFER, geo->getNumVertices() * sizeof(vec3), geo->getVertices(), GL_STATIC_DRAW);

  if (meshes[0]->geometry->getNumIndices() > 0){

	  GLuint elementBufferObject;

	  glGenBuffers(ONE, &elementBufferObject);
	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	  glBufferData(GL_ELEMENT_ARRAY_BUFFER, geo->getNumIndices() * sizeof(GLuint),
		  geo->getIndices(), GL_STATIC_DRAW);

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
	Material* mat = meshes[0]->material;
	Geometry* geo = meshes[0]->geometry;

	glDepthMask(GL_FALSE);
	glUseProgram(mat->id);

	glUniform1f(glGetUniformLocation(mat->id, "time"), _time);

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glBindVertexArray(mat->vertexArrayObject);

	if (geo->getNumIndices() > 0)
		glDrawElements(geo->getDrawMode(), geo->getNumIndices(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(geo->getDrawMode(), 0, geo->getNumVertices());

	glBindVertexArray(CLEAR);
	glUseProgram(CLEAR);

	glBindTexture(GL_TEXTURE_2D, CLEAR);
	glBindFramebuffer(GL_FRAMEBUFFER, CLEAR);
	glDepthMask(GL_TRUE);

}

// @src: http://www.antongerdelan.net/opengl/cubemaps.html
void Skybox::createCubeMap(const char* front, const char* back, const char* top, const char*bottom, const char* left, const char*right){

	glGenTextures(ONE, &(meshes[0]->material->texture));

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
  glBindTexture(GL_TEXTURE_CUBE_MAP, meshes[0]->material->texture);

  int width, height, n;

  unsigned char*  image_data = SOIL_load_image(fileName, &width, &height, &n, SOIL_LOAD_RGBA);

  glTexImage2D(side_target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

  SOIL_free_image_data(image_data);
}

Skybox::~Skybox(){
  // glDeleteTextures(1, &(material->texture));
}

void Skybox::setData(){
	Material* mat = meshes[0]->material;
	glUseProgram(mat->id);

  // Bind the material as texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, mat->texture);

  // Link material texture attribute
  glUniform1i(glGetUniformLocation(mat->id, "cubeSampler"), 0);

  //glBindTexture(GL_TEXTURE_CUBE_MAP, CLEAR);
  glUseProgram(CLEAR);
}