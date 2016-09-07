#include "PhongMaterial.h"

PhongMaterial::PhongMaterial(const char* vertexShader, const char* fragmentShader, const char* geometryShader)
  : Material(vertexShader, fragmentShader, geometryShader){

}

void PhongMaterial::setColor(vec3* color) {
    glUseProgram(id);
    glUniform3fv(glGetUniformLocation(id, "color"), ONE, color->data());
}

void PhongMaterial::setPhongReflection(vec3* ka, vec3* kd, vec3* ks, float p) {
    glUseProgram(id);
    glUniform1f(glGetUniformLocation(id, "p"), p);
    glUniform3fv(glGetUniformLocation(id, "ka"), ONE, ka->data());
    glUniform3fv(glGetUniformLocation(id, "kd"), ONE, kd->data());
    glUniform3fv(glGetUniformLocation(id, "ks"), ONE, ks->data());
}