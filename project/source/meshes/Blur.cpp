#include "Blur.h"

#include "_blur_vshader.h"
#include "_blur_fshader.h"

/*May seem dumb but the way we did it before only copied the first value of the array*/

Blur::Blur(BufferCamera* sceneCamera)
	: Model(new PlaneVert(), new Material(_blur_vshader, _blur_fshader, NULL)) {

  _sceneCamera = sceneCamera;
  setup(sceneCamera,1024, 768);
}

Blur::~Blur() {
	glDeleteTextures(1, &(meshes[0]->material->texture));
}

void Blur::setup(Camera* sceneCamera,GLsizei width, GLsizei height) {
 
  horizontal = true;

  // framebuffer for blurring
  glGenFramebuffers(2, blurFBO);
  glGenTextures(2, blurColorbuffers);
  for (GLuint i = 0; i < 2; i++)
  {
    glBindFramebuffer(GL_FRAMEBUFFER, blurFBO[i]);
    glBindTexture(GL_TEXTURE_2D, blurColorbuffers[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Clamp to the edge as the blur filter would otherwise sample repeated texture values!
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blurColorbuffers[i], 0);

    // Check FBO Correctness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      std::cout << "Framebuffer not complete!" << std::endl;
  }

  // Unbind Framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, CLEAR);

}

void Blur::draw(GLuint frameBuffer, float _time, float _effect) {

	Material * mat = meshes[0]->material;
	Geometry* geo = meshes[0]->geometry;

	GLuint iterations = 20;
	for (GLuint i = 0; i < iterations; i++) {
		glUseProgram(mat->id);
		glBindFramebuffer(GL_FRAMEBUFFER, blurFBO[horizontal]);
		glUniform1i(glGetUniformLocation(mat->id, "horizontal"), horizontal);
		// bind texture of other framebuffer (or scene if first iteration)
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, i == 0 ? _sceneCamera->texture2: blurColorbuffers[!horizontal]);
		glUniform1i(glGetUniformLocation(mat->id, "textureSampler"), 0);

		glBindVertexArray(mat->vertexArrayObject);

		glDrawArrays(geo->getDrawMode(), 0, geo->getNumVertices());

		glBindVertexArray(CLEAR);

		glUseProgram(CLEAR);
		horizontal = !horizontal;
	}




}