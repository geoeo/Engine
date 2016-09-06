#include "Camera.h"

Camera::Camera() {

	Position = vec3(0.0f, 20.0f, 150.0f);
	//Position = vec3(0.0f, 0.0f, 20.0f);
	Front = vec3(0.0f, 0.0f, -1.0f);
	Up = vec3(0.0f, 1.0f, 0.0f);
	WorldUp = vec3(0.0f, 1.0f, 0.0f);
	Yaw = -90.0f;
	Pitch = 0.0f;

	updateCameraVectors();

}

Camera::~Camera() {

}

Camera* Camera::copy() {
  return new Camera();
}

void Camera::animatePositionTo(vec3 pos) {
  animPositionToControls.push_back(pos);
}

void Camera::animateLookAt(vec3 lookAt) {
  animLookAtControls.push_back(lookAt);
}

void Camera::startAnimation(float duration, float start) {
  animDuration = duration;
  animStart = start;
}

void Camera::animate(float _time) {

  float frameToSec = 0.33;

  float t = frameToSec * (_time - animStart) / (animDuration);

  if (frameToSec * _time > animStart) {
    if (animDuration && t >= 0 && t <= 1.0) {
      float timeWithEasing = Bezier::easeInOut(t);
      if (animPositionToControls.size()){
        Position = Bezier::eval3d(&animPositionToControls[0], animPositionToControls.size(), timeWithEasing);
      }
      if (animLookAtControls.size()){
        Front = Bezier::eval3d(&animLookAtControls[0], animLookAtControls.size(), timeWithEasing);
      }
    }
    else {
      animDuration = 0.0;
    }
  }
  updateViewMatrix();
}

void Camera::update() {
  this->updateModelMatrix();
  this->updateViewMatrix();
  this->updateProjectionMatrix();
}

void Camera::updateViewMatrix() {
  //this->view = Eigen::lookAt(position, lookAt, up) * model;
  vec3 v = Position + Front;
  view = Eigen::lookAt(Position,v , Up);
}

void Camera::updateProjectionMatrix() {
  this->projection = mat4::Identity();
}

void Camera::onResize(const Event& e) {

}

void Camera::onMouseInput(const Event& e) {

  const MouseEvent& event = static_cast<const MouseEvent&>( e );

  bool view_matrices_changed = false;
  static int current_state = -1;

  const float x = 2.0f * static_cast<float>(event.xpos) / event.windowWidth - 1.0f;
  const float y = 1.0f - 2.0f * static_cast<float>(event.ypos) / event.windowHeight;

  static double old_x = event.xpos;
  static double old_y = event.ypos;
  static mat4 old_rotation = mat4::Identity();

  const float dx = event.xpos - old_x;
  const float dy = event.ypos - old_y;

  old_x = event.xpos;
  old_y = event.ypos;

  double cursorXFromMiddle = double(event.windowWidth / 2);
  double cursorYFromMiddle = double(event.windowHeight / 2);

  if (event.action == GLFW_PRESS) {
    current_state = event.mod;
  }

  if (event.button == GLFW_MOUSE_BUTTON_LEFT && event.action == GLFW_PRESS) {


    old_rotation = _rotation;
    trackball.BeginDrag(x, y);

	if (dx > 0)
		this->Yaw += 10;
	else if (dx < 0)
		this->Yaw -= 10;

	if (dy > 0)
		this->Pitch += 10;
	else if (dy < 0)
		this->Pitch -= 10;


	if (this->Pitch > 89.0f)
		this->Pitch = 89.0f;
	if (this->Pitch < -89.0f)
		this->Pitch = -89.0f;

	this->updateCameraVectors();
  }

  // Maya style controls.
  if ( event.leftDown && current_state == GLFW_MOD_NONE ) {
    trackball.Drag(x, y);
    mat4 rot = trackball.incremental_rotation();
    if (rot.norm() > 0.0) {
      _rotation = trackball.incremental_rotation() * old_rotation;

    view_matrices_changed = true;
    }

  }

  // Pan
  if ( event.middleDown || (event.leftDown && (current_state == GLFW_MOD_SHIFT || current_state == GLFW_MOD_CONTROL)) ) {
    const float s = 0.05f;
    _translation *= Eigen::Affine3f(Eigen::Translation3f(s * dx, -s * dy, 0.0f)).matrix();
    view_matrices_changed = true;
  }

  // Zoom
  if ( event.rightDown || (event.leftDown && (current_state == GLFW_MOD_ALT || current_state == GLFW_MOD_SUPER)) ) {
    const float s = 0.05f;
    _translation *= Eigen::Affine3f(Eigen::Translation3f(0.0f, 0.0f, s * dy)).matrix();
    view_matrices_changed = true;
  }

  if (view_matrices_changed) {
    this->updateModelMatrix();
	this->updateViewMatrix();
  }

  
}

void Camera::onWheelInput(const Event& e) {

  const WheelEvent& event = static_cast<const WheelEvent&>( e );

  const float s = 0.05f;
  _translation *= Eigen::Affine3f(Eigen::Translation3f(s * event.dx, 0.0f, s * event.dy)).matrix();
  this->updateModelMatrix();
  this->updateViewMatrix();
}

void Camera::onKeyInput(const Event& e) {

  const KeyEvent& event = static_cast<const KeyEvent&>( e );

  float deltaTime = 0.5;

  bool view_matrices_changed = false;
  static mat4 old_rotation = mat4::Identity();

  // Control parameters
  float speed = 20.0; // 3 units / second

  // Reset the view
  if (event.key == GLFW_KEY_R && event.action == GLFW_PRESS){
    _scale = mat4::Identity();
    _rotation = mat4::Identity();
    _translation = mat4::Identity();
    old_rotation = mat4::Identity();
    view_matrices_changed = true;
  }

  const float moveComponent = 1.5f;

  /*Move forward*/
  if (event.key == GLFW_KEY_W && event.action == GLFW_PRESS){
    _translation *= Eigen::Affine3f(Eigen::Translation3f(0.0f, 0.0f, moveComponent)).matrix();
	Position += 1 * Front;
    view_matrices_changed = true;
  }

  /*Move backward*/
  if ( event.key == GLFW_KEY_S && event.action == GLFW_PRESS){
    _translation *= Eigen::Affine3f(Eigen::Translation3f(0.0, 0.0, -moveComponent)).matrix();
	Position -= 1 * Front;
    view_matrices_changed = true;
  }

  /*Move right*/
  if  (event.key == GLFW_KEY_D && event.action == GLFW_PRESS){
    _translation *= Eigen::Affine3f(Eigen::Translation3f(-moveComponent, 0.0, 0.0)).matrix();
	Position += this->Right * 1;
    view_matrices_changed = true;
  }

  /*Move left*/
  if (event.key == GLFW_KEY_A && event.action == GLFW_PRESS){
    _translation *= Eigen::Affine3f(Eigen::Translation3f(moveComponent, 0.0, 0.0)).matrix();
	Position -= this->Right *1 ;
    view_matrices_changed = true;
  }

  /* Crude Control for Heightmap*/
  if (event.key == GLFW_KEY_2 && event.action == GLFW_PRESS) {
	  if (effect_roll < 1) {
		  effect_roll += 0.1;
	  }
  }

  if (event.key == GLFW_KEY_1 && event.action == GLFW_PRESS) {
	  if (effect_roll > 0) {
		  effect_roll -= 0.1;
	  }
  }

  if (event.key == GLFW_KEY_LEFT && event.action == GLFW_PRESS) {
	  this->Yaw -= 5;
	  this->updateCameraVectors();
	  view_matrices_changed = true;
  }

  if (event.key == GLFW_KEY_RIGHT && event.action == GLFW_PRESS) {
	  this->Yaw += 5;
	  this->updateCameraVectors();
	  view_matrices_changed = true;
  }

  if (event.key == GLFW_KEY_UP && event.action == GLFW_PRESS) {
	  this->Pitch += 5;
	  if (this->Pitch > 89.0f)
		  this->Pitch = 89.0f;
	  this->updateCameraVectors();
	  view_matrices_changed = true;
  }

  if (event.key == GLFW_KEY_DOWN && event.action == GLFW_PRESS) {
	  this->Pitch -= 5;
	  if (this->Pitch < -89.0f)
		  this->Pitch = -89.0f;
	  this->updateCameraVectors();
	  view_matrices_changed = true;
  }

  

  if (view_matrices_changed) {
    this->updateModelMatrix();
    this->updateViewMatrix();
  }
}

void Camera::onLeapInput(const Event& e) {

  const LeapEvent& event = static_cast<const LeapEvent&>( e );

  static float roll = 0.0;
  static float yaw = 0.0;
  static float pitch = 0.0;

  const float smoothFactor = 0.5;
  bool view_matrices_changed = false;
  static mat4 old_rotation = mat4::Identity();

  // roll += (event.roll - roll) * smoothFactor;
  // yaw += (event.yaw - yaw) * smoothFactor;
  // pitch += (event.pitch - pitch) * smoothFactor;

  roll = event.roll;
  yaw = event.yaw;
  pitch = event.pitch;

  // @src: http://stackoverflow.com/a/21414609
  Eigen::AngleAxisf rollAngle(-roll, vec3::UnitZ());
  Eigen::AngleAxisf yawAngle(yaw, vec3::UnitY());
  Eigen::AngleAxisf pitchAngle(pitch, vec3::UnitX());

  mat4 rot = Eigen::Affine3f(rollAngle * yawAngle * pitchAngle).matrix();

  old_rotation = _rotation;
  _rotation = rot;

  this->updateModelMatrix();
  this->updateViewMatrix();
}

void Camera::onLeapLeftInput(const Event& e) {

  const LeapLeftEvent& event = static_cast<const LeapLeftEvent&>( e );

  effect_roll = event.roll;
  effect_yaw = event.yaw;
  effect_pitch = event.pitch;

  // printf("Roll: %f\n", event.roll);
  // printf("Yaw: %f\n", event.yaw);
  // printf("Pitch: %f\n", event.pitch);
}

void Camera::setData(GLuint id){
  glUseProgram(id);
  glUniform3f(glGetUniformLocation(id, "camPos"), this->Position.x(),this->Position.y(),this->Position.z());
  glUniform1f(glGetUniformLocation(id, "effectPitch"), effect_pitch);
  glUniform1f(glGetUniformLocation(id, "effectYaw"), effect_yaw);
  glUniform1f(glGetUniformLocation(id, "effectRoll"), effect_roll);
}

mat4 Camera::orthographic(float left, float right, float bottom, float top, float near, float far) {
  mat4 omat;
  omat << 2.0 / (right-left), 0.0, 0.0, 0.0,
          0.0, 2.0 / (top-bottom), 0.0, 0.0,
          0.0, 0.0, -2.0 / (far-near), 0.0,
          -(right+left)/(right-left), -(top+bottom)/(top-bottom), -(far+near)/(far-near), 1.0;

  return omat;
}