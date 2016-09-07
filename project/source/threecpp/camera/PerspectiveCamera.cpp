#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float _fieldOfView, float _aspectRatio, float _nearPlane, float _farPlane, bool _debugOrtho): Camera() {
  fieldOfView = _fieldOfView;
  aspectRatio = _aspectRatio;
  nearPlane = _nearPlane;
  farPlane = _farPlane;
  debugOrtho = _debugOrtho;
}

PerspectiveCamera::~PerspectiveCamera() {

}

PerspectiveCamera* PerspectiveCamera::copy() {
  return new PerspectiveCamera(fieldOfView, aspectRatio, nearPlane, farPlane,false);
}

void PerspectiveCamera::updateProjectionMatrix() {
  if(debugOrtho)
	this->projection = Eigen::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, 0.1f, -5.0f);
  else
	this->projection = Eigen::perspective(fieldOfView, aspectRatio, nearPlane, farPlane);
 
}

void PerspectiveCamera::onResize(const Event& e) {

  const ResizeEvent& event = static_cast<const ResizeEvent&>( e );

  aspectRatio = float(event.width / event.height);

  this->updateProjectionMatrix();
}