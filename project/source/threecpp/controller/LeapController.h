#pragma once

#include <iostream>
#include <string.h>

#include "Leap.h"
#include "Events.h"

#ifdef __unix__ 
class LeapController: public Dispatcher, Leap::Listener {

private:
  Leap::Controller controller;

public:

  // Constructor
  LeapController();

  // Destructor
  ~LeapController();

  void onConnect(const Leap::Controller&);
  void onFrame(const Leap::Controller&);
};
#endif