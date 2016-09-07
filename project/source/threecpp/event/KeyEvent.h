#pragma once

#include "Event.h"

class KeyEvent : public Event {

public:

  int key;
  int scancode;
  int action;
  int mods;

  KeyEvent(int, int, int, int);
  virtual ~KeyEvent();

  virtual DescriptorType type() const {
    return "KeyEvent";
  }
};