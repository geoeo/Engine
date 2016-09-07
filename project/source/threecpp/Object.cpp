#include "Object.h"

Object::~Object() {

}

void Object::rotateX(float rot) {
  rotate(rot, vec3::UnitX());
}

void Object::rotateY(float rot) {
  rotate(rot, vec3::UnitY());
}

void Object::rotateZ(float rot) {
  rotate(rot, vec3::UnitZ());
}

void Object::rotate(float rot, vec3 axis) {
  _rotation *= Eigen::Affine3f(Eigen::AngleAxisf(rot, axis)).matrix();
  updateModelMatrix();
}

void Object::scale(float s) {
  _scale *= Eigen::Affine3f(Eigen::Scaling(s)).matrix();
  updateModelMatrix();
}

void Object::scale(float sx, float sy, float sz) {
  _scale *= Eigen::Affine3f(Eigen::Scaling(sx, sy, sz)).matrix();
  updateModelMatrix();
}

void Object::translate(float tx, float ty, float tz) {
  _translation += Eigen::Affine3f(Eigen::Translation3f(tx, ty, tz)).matrix();
  updateModelMatrix();
}

void Object::resetScale() {
  _scale = mat4::Identity();
  updateModelMatrix();
}

void Object::resetTranslation() {
  _translation = mat4::Identity();
  updateModelMatrix();
}

void Object::resetRotation() {
  _rotation = mat4::Identity();
  updateModelMatrix();
}

void Object::updateModelMatrix() {
  model = _translation * _rotation * _scale;
}