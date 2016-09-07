#include "BufferCamera.h"

BufferCamera* BufferCamera::fromCamera(PerspectiveCamera* camera, bool debugOrtho) {

  // Initialize a new Camera, with same properties as camera
	BufferCamera* buf = new BufferCamera(
		camera->fieldOfView,
		camera->aspectRatio,
		camera->nearPlane,
		camera->farPlane,
		debugOrtho
  );

  buf->position = camera->position;
  buf->lookAt= camera->lookAt;
  buf->up = camera->up;
  buf->update();

  // return the Camera
  return buf;
}


BufferCamera::BufferCamera(float _fieldOfView, float _aspectRatio, float _nearPlane, float _farPlane, bool debugOrtho)
  : PerspectiveCamera(_fieldOfView, _aspectRatio, _nearPlane, _farPlane, debugOrtho) {

}

BufferCamera::~BufferCamera() {

}

GLuint BufferCamera::createTexture(GLsizei width, GLsizei height, bool isDepth) {
  GLuint id;

  glGenTextures(ONE, &id);

  // "Bind" the newly created texture : all future texture functions will modify this texture
  glBindTexture(GL_TEXTURE_2D, id);

  // void glTexImage2D(GLenum target, GLint level, GLint internalFormat,
  // GLsizei width, GLsizei height,
  // GLint border, GLenum format, GLenum type, const GLvoid * data);
  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    (isDepth ? GL_DEPTH_COMPONENT32F : GL_RGBA),
    width,
    height,
    0,
    (isDepth ? GL_DEPTH_COMPONENT :  GL_RGBA),
    GL_FLOAT,
    NULL
  );

  if (isDepth) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Remove artifact on the edges of the shadowmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER_ARB );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER_ARB );

 //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
 //   glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
  }
  else {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  }

  // Error Handling
  int error = glGetError();
  if (error!= 0) {
      std::cerr << "Cannot load Texture. Error: " << error << std::endl;
  }

  // Unbind Texture
  glBindTexture(GL_TEXTURE_2D, 0);

  return id;
}

void BufferCamera::createFrameBuffer(GLsizei width, GLsizei height, bool isDepth, bool isBloom) {

	if (isBloom){
		texture2 = createTexture(width, height,false);
	}

  // Create a new Render target texture
  texture = createTexture(width, height, isDepth);


  // Create one OpenGL framebuffer
  glGenFramebuffers(ONE, &frameBuffer);

  // "Bind" the newly created framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

  // GL_COLOR_ATTACHMENTi or GL_DEPTH_ATTACHMENT
  glFramebufferTexture2D(
    GL_FRAMEBUFFER,
    (isDepth ? GL_DEPTH_ATTACHMENT : GL_COLOR_ATTACHMENT0),
    GL_TEXTURE_2D,
    texture,
    0
  );

  if (isBloom){

	  glFramebufferTexture2D(
		  GL_FRAMEBUFFER,
		  GL_COLOR_ATTACHMENT1,
		  GL_TEXTURE_2D,
		  texture2,
		  0);

	  glGenRenderbuffers(1, &depthBuffer);
	  glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);
	  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	  glDrawBuffers(2,attachments);


  }

  if (isDepth) {
    // No color output in the bound framebuffer, only depth.
    glDrawBuffer(GL_NONE);
    //glReadBuffer(GL_NONE);
  }

  // Error Handling
  if(glCheckFramebufferStatus(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE){
    std::cerr << "Framebuffer not complete." <<std::endl;
  }

  // Unbind Framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, CLEAR);

}