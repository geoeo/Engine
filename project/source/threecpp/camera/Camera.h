#pragma once

#include "../globals.h"
#include "Events.h"
#include "Object.h"
#include "Geometries.h"

#include <Eigen/Dense>
#include <OpenGP/GL/Trackball.h>

class Camera: public Object {

private:
  Trackball trackball;
  float animDuration = 0.0;
  float animStart = 0.0;
  std::vector<vec3> animPositionToControls;
  std::vector<vec3> animLookAtControls;

protected:

  void updateViewMatrix();
  virtual void updateProjectionMatrix();

public:

  /* NEW IMPLEMENTATION */
  // Camera Attributes 
	 vec3 Position;
	 vec3 Front;
	 vec3 Up;
	 vec3 Right;
	 vec3 WorldUp = vec3(0,1,0);
	 // Eular Angles 
	 GLfloat Yaw;
	 GLfloat Pitch;
	 // Camera options 
	 GLfloat MovementSpeed;
	 GLfloat MouseSensitivity;
	 GLfloat Zoom;

	 /* NEW IMPLEMENTATION END */


  vec3 position;

  float effect_roll = 0.0;
  float effect_pitch = 0.0;
  float effect_yaw = 0.0;

  float effect_roll_speed;
  float effect_pitch_speed;
  float effect_yaw_speed;

  // Camera View Matrix
  mat4 view;

  // Camera Projection Matrix
  mat4 projection;

  // Look at vector
  vec3 lookAt;

  // Up vector
  vec3 up;

  // Framebuffer
  GLuint frameBuffer;

  GLuint depthBuffer;

  // Constructor
  Camera();

  // Destructor

  bool debugOrtho = false;
  ~Camera();

  void update();
  virtual void onResize(const Event&);
  void onMouseInput(const Event&);
  void onWheelInput(const Event&);
  void onKeyInput(const Event&);
  virtual void onLeapInput(const Event&);
  virtual void onLeapLeftInput(const Event&);

  Camera* copy();
  virtual void setData(GLuint);
  void animate(float);

  void animatePositionTo(vec3);
  void animateLookAt(vec3);
  void startAnimation(float, float start = 0.0);

  static mat4 orthographic(float, float, float, float, float, float);

  void updateCameraVectors()
  {
	// Calculate the new Front vector 
	Front = vec3(cos(radians(this->Yaw)) * cos(radians(this->Pitch)), sin(radians(this->Pitch)), sin(radians(this->Yaw)) * cos(radians(this->Pitch)));
	this->Front.normalize();
	// Also re-calculate the Right and Up vector 
	this->Right = this->Front.cross(this->WorldUp);  
	this->Right.normalize();// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement. 
	this->Up = this->Right.cross(this->Front);
	this->Up.normalize();
  }

  float radians(float degrees) {
	  return M_PI * degrees / 180;
  }

};