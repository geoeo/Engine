#pragma once

#include "common.h"
#include "Event.h"

class WheelEvent : public Event {

public:

  double xpos;
  double ypos;
  double dx;
  double dy;

  bool leftDown = false;
  bool middleDown = false;
  bool rightDown = false;

  int windowWidth;
  int windowHeight;

  WheelEvent(GLFWwindow*, double, double);
  virtual ~WheelEvent();

  virtual DescriptorType type() const {
    return "WheelEvent";
  }
};