#pragma once

#include "common.h"
#include "PerspectiveCamera.h"

static const GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };

class BufferCamera: public PerspectiveCamera {

private:
  GLuint createTexture(GLsizei, GLsizei, bool _isDepth = false);


public:
  // Constructor
  BufferCamera(float, float, float, float,bool);

  // Destructor
  ~BufferCamera();

  // Texture
  GLuint texture;
  GLuint texture2; // optional second render target
  GLuint depthTexture;

  // GBuffer Textures
  GLuint gPositionDepth;
  GLuint gNormal;
  GLuint gAlbedoSpec;

  void createFrameBuffer(GLsizei, GLsizei, bool isDepth = false, bool isBlur = false);
  void createGBuffer(GLsizei width, GLsizei height);

  static BufferCamera* fromCamera(PerspectiveCamera*, bool);
};