#pragma once

#include "common.h"
#include "Event.h"

class MouseEvent : public Event {

public:

  double xpos;
  double ypos;
  int button;
  int action;
  int mod;

  bool leftDown = false;
  bool middleDown = false;
  bool rightDown = false;

  int windowWidth;
  int windowHeight;

  MouseEvent(GLFWwindow*, int, int, int);
  virtual ~MouseEvent();

  virtual DescriptorType type() const {
    return "MouseEvent";
  }
};