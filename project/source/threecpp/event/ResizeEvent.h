#pragma once

#include "Event.h"

class ResizeEvent : public Event {

public:

  int width;
  int height;

  ResizeEvent(int, int);
  virtual ~ResizeEvent();

  virtual DescriptorType type() const {
    return "ResizeEvent";
  }
};