#ifdef __unix__  
#include "LeapController.h"

 
LeapController::LeapController() {
  controller.addListener(*this);
}

LeapController::~LeapController() {
  controller.removeListener(*this);
}


void LeapController::onConnect(const Leap::Controller& controller) {
  // Successfully connected to Leap
}

void LeapController::onFrame(const Leap::Controller& controller) {
  const Leap::Frame frame = controller.frame();
  Leap::HandList hands = frame.hands();

  Leap::Hand leftmost = hands.leftmost();
  Leap::Hand rightmost = hands.rightmost();

  if (leftmost.isValid() && leftmost.isLeft()) {
    // pitch (angle around the x-axis)
    float pitch = leftmost.direction().pitch();

    // yaw (angle around the y-axis)
    float yaw = leftmost.direction().yaw();

    // roll (angle around the z-axis)
    float roll = leftmost.palmNormal().roll();

    this->notify(LeapLeftEvent(pitch, yaw, roll));
  }

  if (rightmost.isValid() && rightmost.isRight()) {
    // pitch (angle around the x-axis)
    float pitch = rightmost.direction().pitch();

    // yaw (angle around the y-axis)
    float yaw = rightmost.direction().yaw();

    // roll (angle around the z-axis)
    float roll = rightmost.palmNormal().roll();

    this->notify(LeapEvent(pitch, yaw, roll));
  }
}
#endif