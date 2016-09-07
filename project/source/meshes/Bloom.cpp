#include "Bloom.h"

#include "_bloom_vshader.h"
#include "_bloom_fshader.h"

/*May seem dumb but the way we did it before only copied the first value of the array*/

Bloom::Bloom(BufferCamera* sceneCamera, Blur* blurMesh)
	: Model(new PlaneVert(), new Material(_bloom_vshader, _bloom_fshader, NULL)) {

  _sceneCamera = sceneCamera;
  _blurMesh = blurMesh;

}

Bloom::~Bloom() {
  //glDeleteTextures(1, &(material->texture));
}

void Bloom::setup(Camera* sceneCamera, GLsizei width, GLsizei height) {
 



}

void Bloom::draw(GLuint frameBuffer, float _time, float _effect) {

	Material * mat = meshes[0]->material;
	Geometry* geo = meshes[0]->geometry;

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Blend scene and blur texture
	glUseProgram(mat->id);
	// Set our "scene" sampler to user Texture Unit 0 
	glUniform1i(glGetUniformLocation(mat->id, "scene"), 0);
	glUniform1i(glGetUniformLocation(mat->id, "bloomBlur"), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _sceneCamera->texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _blurMesh->blurColorbuffers[!_blurMesh->horizontal]);

	glBindVertexArray(mat->vertexArrayObject);

	glDrawArrays(geo->getDrawMode(), 0, geo->getNumVertices());

	glBindVertexArray(CLEAR);


	glUseProgram(CLEAR);





}