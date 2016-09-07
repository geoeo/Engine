#pragma once

#include "Event.h"

class UpdateEvent : public Event {

public:
  double time;

  UpdateEvent(double);
  virtual ~UpdateEvent();

  virtual DescriptorType type() const {
    return "UpdateEvent";
  }
};