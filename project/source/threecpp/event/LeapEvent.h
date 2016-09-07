#pragma once

#include "common.h"
#include "Event.h"

class LeapEvent : public Event {

public:

  float pitch;
  float yaw;
  float roll;

  LeapEvent(float, float, float);
  virtual ~LeapEvent();

  virtual DescriptorType type() const {
    return "LeapEvent";
  }
};