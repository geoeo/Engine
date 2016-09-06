#pragma once

#include "common.h"
#include "Scene.h"
#include "Events.h"
#include "Cameras.h"
#include "Controllers.h"

class Window: public Dispatcher {

private:

  // Window reference
  GLFWwindow* ref;

  void setupOpenGL();
  void resetViewport();

  void onLeapInput(const Event&);
  void onLeapLeftInput(const Event&);

  void addKeypressDispatcher();
  void addMousemoveDispatcher();
  void addMousedownDispatcher();
  void addMousewheelDispatcher();
  void addResizeDispatcher();
#ifdef __unix__
  void addLeapDispatcher();
#endif

public:

  static const int WINDOW_SUCCESS = 1;
  static const int WINDOW_ERROR = 0;

  // Window dimensions
  int width;
  int height;

  // Constructor
  Window(int, int);

  // Destructor
  ~Window();

  int create();
  void startEventLoop();
  int destroy();

  void registerScene(Scene*);
  void registerCamera(Camera*);
  void registerBuffer(BufferCamera*);
};