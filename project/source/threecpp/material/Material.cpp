#include "Material.h"

Material::Material(const char* vertexShader, const char* fragmentShader, const char* geometryShader){

  id = compile_shaders(vertexShader, fragmentShader, geometryShader);

  if (!id) {
    // TODO: Would be great to have some proper error handling here
    exit(EXIT_FAILURE);
  }
}

Material::~Material(){

}

void Material::setMVP(const mat4& object, const mat4& model, const mat4& view, const mat4& projection) {
  glUseProgram(id);

  mat4 combinedModelMatrix = /* model * */ object;

  GLuint modelId = glGetUniformLocation(id, "model");
  glUniformMatrix4fv(modelId, ONE, DONT_TRANSPOSE, combinedModelMatrix.data());

  GLuint projectionId = glGetUniformLocation(id, "projection");
  glUniformMatrix4fv(projectionId, ONE, DONT_TRANSPOSE, projection.data());

  GLuint viewId = glGetUniformLocation(id, "view");
  glUniformMatrix4fv(viewId, ONE, DONT_TRANSPOSE, view.data());

  glUseProgram(CLEAR);
}

GLuint Material::loadTexture(const char* fileName, bool isDepth, GLenum edge){
  GLuint id;

  glGenTextures(ONE, &id);

  // "Bind" the newly created texture : all future texture functions will modify this texture
  glBindTexture(GL_TEXTURE_2D, id);

  int width, height, n;

  unsigned char* image_data = SOIL_load_image(fileName, &width, &height, &n, SOIL_LOAD_RGBA);

  // void glTexImage2D(GLenum target, GLint level, GLint internalFormat,
  // GLsizei width, GLsizei height,
  // GLint border, GLenum format, GLenum type, const GLvoid * data);
  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    (isDepth ? GL_DEPTH_COMPONENT32 : GL_RGBA),
    width,
    height,
    0,
    (isDepth ? GL_DEPTH_COMPONENT : GL_RGBA),
    GL_UNSIGNED_BYTE,
    image_data
  );

  if (isDepth) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Remove artifact on the edges of the shadowmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
  }
  else {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, edge);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, edge);
  }

  // Error Handling
  int error = glGetError();
  if (error!= 0) {
      std::cerr << "Cannot load Texture. Error: " << error << std::endl;
  }

  SOIL_free_image_data(image_data);

  // Unbind Texture
  glBindTexture(GL_TEXTURE_2D, 0);

  return id;
}