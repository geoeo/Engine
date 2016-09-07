#include "StaticMaterial.h"

StaticMaterial::StaticMaterial(const char* vertexShader, const char* fragmentShader, const char* geometryShader)
  : Material(vertexShader, fragmentShader, geometryShader){

}

void StaticMaterial::setMVP(const mat4& object, const mat4& model, const mat4& view, const mat4& projection) {
  glUseProgram(id);

  GLuint modelId = glGetUniformLocation(id, "model");
  glUniformMatrix4fv(modelId, ONE, DONT_TRANSPOSE, object.data());

  glUseProgram(CLEAR);
}