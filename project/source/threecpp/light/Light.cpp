#include "Light.h"

Light::Light(const char* _desc) {
  descriptor = _desc;

  offsetMatrix << 0.5, 0.0, 0.0, 0.5,
                  0.0, 0.5, 0.0, 0.5,
                  0.0, 0.0, 0.5, 0.5,
                  0.0, 0.0, 0.0, 1.0;

  //projection = Eigen::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 0.1f, 1000.0f);
  //projection = Eigen::perspective(80.0f, ASPECT, NEAR, FAR);
  projection = Eigen::ortho(-ASPECT, ASPECT, -1.0f, 1.0f, 0.1f, 5.0f);
 
}

Light::~Light() {

}

mat4 Light::getMVP(){
  mat4 view = Eigen::lookAt(position, lookAt, up);
  // Assemble the "Light Model View Projection" matrix
  return projection * view;
}

void Light::setData(GLuint id) {
  glUseProgram(id);

  glUniform3fv(glGetUniformLocation(id, (string(descriptor) + "Pos").data()), ONE, position.data());
  glUniform3fv(glGetUniformLocation(id, (string(descriptor) + "Ia").data()), ONE, Ia.data());
  glUniform3fv(glGetUniformLocation(id, (string(descriptor) + "Id").data()), ONE, Id.data());
  glUniform3fv(glGetUniformLocation(id, (string(descriptor) + "Is").data()), ONE, Is.data());

  // Compute the light lookup MVP
  mat4 lightOffsetMVP;
  lightOffsetMVP = /* offsetMatrix * */ getMVP();

  GLuint lightOffsetMvpID = glGetUniformLocation(id, "lightOffsetMVP");
  glUniformMatrix4fv(lightOffsetMvpID, ONE, DONT_TRANSPOSE, lightOffsetMVP.data());
}