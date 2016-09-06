#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float _left, float _right, float _bottom, float _top, float _near, float _far) {
  left = _left;
  right = _right;
  bottom = _bottom;
  top = _top;
  near = _near;
  far = _far;
}

OrthographicCamera::~OrthographicCamera() {

}

OrthographicCamera* OrthographicCamera::copy() {
  return new OrthographicCamera(left, right, bottom, top, near, far);
}

void OrthographicCamera::updateProjectionMatrix() {
  this->projection = Camera::orthographic(left, right, bottom, top, near, far);
}