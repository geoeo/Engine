#pragma once

#include "common.h"
#include "Event.h"

class LeapLeftEvent : public Event {

public:

  float pitch;
  float yaw;
  float roll;

  LeapLeftEvent(float, float, float);
  virtual ~LeapLeftEvent();

  virtual DescriptorType type() const {
    return "LeapLeftEvent";
  }
};