#include "DeferredQuad.h"

#include "_pass_vshader.h"
#include "_gBuffer_fshader.h"

DeferredQuad::DeferredQuad(BufferCamera* gBufferCamera) 
	: Model(new PlaneVert(), new Material(_pass_vshader, _gBuffer_fshader, NULL)) {

	_gBufferCamera = gBufferCamera;

}

DeferredQuad::~DeferredQuad() {
	glDeleteTextures(1, meshes[0]->material->textures);
}

void DeferredQuad::setData(){

	Material* mat = meshes[0]->material;

	glUseProgram(mat->id);

	// Bind the material as texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _gBufferCamera->gPosition);
	// Link material texture attribute
	glUniform1i(glGetUniformLocation(mat->id, "gPosition"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _gBufferCamera->gNormal);
	glUniform1i(glGetUniformLocation(mat->id, "gNormal"), 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _gBufferCamera->gAlbedoSpec);
	glUniform1i(glGetUniformLocation(mat->id, "gAlbedoSpec"), 2);

	glUniform3f(glGetUniformLocation(mat->id, "camPos"), _gBufferCamera->Position.x(), _gBufferCamera->Position.y(), _gBufferCamera->Position.z());

	glUseProgram(CLEAR);

}

void DeferredQuad::draw(GLuint frameBuffer, float _time, float _effect) {

	Material * mat = meshes[0]->material;
	Geometry* geo = meshes[0]->geometry;

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Blend scene and blur texture
	glUseProgram(mat->id);

	glBindVertexArray(mat->vertexArrayObject);

	glDrawArrays(geo->getDrawMode(), 0, geo->getNumVertices());

	glBindVertexArray(CLEAR);


	glUseProgram(CLEAR);





}