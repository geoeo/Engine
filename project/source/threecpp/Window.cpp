#include "Window.h"

Window::Window(int _width, int _height) {
  width = _width;
  height = _height;

  // Set the Error Callback function to output to errors to stderr
  auto _onError = [](int error, const char* description) {
    fputs(description, stderr);
  };
  glfwSetErrorCallback(_onError);

  // Create and initialize a Window using GLFW, GLEW and OpenGL
  if (!create()) {
    fprintf(stderr, "ERROR: An error occurred while creating the widow!\n");
    exit(EXIT_FAILURE);
  }
}

Window::~Window() {

}

void Window::setupOpenGL() {
  // Wait exactly one frame to swap the buffer
  glfwSwapInterval(1);

  // Print Out Current OpenGL Version
  fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

  // Prepare for OpenGL rendering
  glfwGetFramebufferSize(ref, &width, &height);
  this->resetViewport();
}

void Window::resetViewport() {
  // Resize the viewport
  glViewport(0, 0, width, height);
}

int Window::create() {

  // Initialize GLFW
  if (!glfwInit()) {
    return WINDOW_ERROR;
  }

  // Create a window and its OpenGL context
  ref = glfwCreateWindow(width, height, "Project", NULL, NULL);
  if (!ref) {
    glfwTerminate();
    return WINDOW_ERROR;
  }

  // Make the window's context current
  glfwMakeContextCurrent(ref);

  // Hack, to use $this inside the callback
  // @src: http://stackoverflow.com/a/28660673
  glfwSetWindowUserPointer(ref, this);

  // Initialize GLEW
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    // Problem: glewInit failed, something is seriously wrong
    // fprintf(stderr, "Glew Init Error: %s\n", glewGetErrorString(err));
    glfwTerminate();
    return WINDOW_ERROR;
  }

  // Setup OpenGL
  this->setupOpenGL();

  // Add event dispatchers
  this->addKeypressDispatcher();
  this->addResizeDispatcher();
  this->addMousemoveDispatcher();
  this->addMousedownDispatcher();
  this->addMousewheelDispatcher();
#ifdef __unix__
  this->addLeapDispatcher();
#endif

  return WINDOW_SUCCESS;
}

void Window::addKeypressDispatcher() {
  auto _onKeyInput = [](GLFWwindow* w, int key, int scancode, int action, int mods) {
    // Get the window reference
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(w));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      glfwSetWindowShouldClose(w, GL_TRUE);
    }
    else {
      // Notify the subscribers about an update event
      self->notify(KeyEvent(key, scancode, action, mods));
    }
  };
  glfwSetKeyCallback(ref, _onKeyInput);
}

void Window::addResizeDispatcher() {
  auto _onResize = [](GLFWwindow* w, int width, int height) {
    // Get the window reference
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(w));

    self->width = width;
    self->height = height;

    // Reset the viewport
    self->resetViewport();

    // Notify the subscribers about an update event
    self->notify(ResizeEvent(width, height));
  };
  glfwSetWindowSizeCallback (ref, _onResize);
}

void Window::addMousemoveDispatcher() {
  auto _onMouseInput = [](GLFWwindow* w, double xpos, double ypos) {
    // Get the window reference
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(w));

    // Notify the subscribers about an update event
    self->notify(MouseEvent(w, -1, -1, GLFW_MOD_NONE));
  };
  glfwSetCursorPosCallback (ref, _onMouseInput);
}

void Window::addMousedownDispatcher() {
  auto _onMousedown = [](GLFWwindow* w, int button, int action, int mod) {
    // Get the window reference
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(w));

    // Notify the subscribers about an update event
    self->notify(MouseEvent(w, button, action, mod));
  };
  glfwSetMouseButtonCallback(ref, _onMousedown);
}

void Window::addMousewheelDispatcher() {
  auto _onMousewheel = [](GLFWwindow* w, double dx, double dy) {
    // Get the window reference
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(w));

    // Notify the subscribers about an update event
    self->notify(WheelEvent(w, dx, dy));
  };
  glfwSetScrollCallback(ref, _onMousewheel);
}
#ifdef __unix__
void Window::onLeapInput(const Event& e) {
  const LeapEvent& event = static_cast<const LeapEvent&>( e );

  // Notify Subscribers
  this->notify(event);
}
#endif

#ifdef __unix__
void Window::onLeapLeftInput(const Event& e) {
  const LeapLeftEvent& event = static_cast<const LeapLeftEvent&>( e );

  // Notify Subscribers
  this->notify(event);
}
#endif

#ifdef __unix__
void Window::addLeapDispatcher() {

  // Setup a new Leap Controller
  LeapController* controller = new LeapController();

  // Listen on the Controller for changes
  controller->subscribe("LeapEvent",
    std::bind( &Window::onLeapInput, this, std::placeholders::_1 ));

  // Listen on the Controller for changes
  controller->subscribe("LeapLeftEvent",
    std::bind( &Window::onLeapLeftInput, this, std::placeholders::_1 ));
}
#endif

void Window::registerScene(Scene* _scene) {
  // Subscribe the scene for key events on the window
  this->subscribe("KeyEvent",
    std::bind( &Scene::onKeyInput, _scene, std::placeholders::_1 ));

  // Subscribe the scene for update events on the window
  this->subscribe("UpdateEvent",
    std::bind( &Scene::update, _scene, std::placeholders::_1 ));
}

void Window::registerBuffer(BufferCamera* _camera) {
  // Subscribe the scene for key events on the window
  this->subscribe("ResizeEvent",
    std::bind( &BufferCamera::onResize, _camera, std::placeholders::_1 ));

  // Subscribe the scene for key events on the window
  this->subscribe("KeyEvent",
    std::bind( &BufferCamera::onKeyInput, _camera, std::placeholders::_1 ));

  // Subscribe the scene for mouse events on the window
  this->subscribe("MouseEvent",
    std::bind( &BufferCamera::onMouseInput, _camera, std::placeholders::_1 ));

  // Subscribe the scene for wheel events on the window
  this->subscribe("WheelEvent",
    std::bind( &BufferCamera::onWheelInput, _camera, std::placeholders::_1 ));

  // Subscribe the scene for Leap events on the window
  this->subscribe("LeapEvent",
    std::bind( &BufferCamera::onLeapInput, _camera, std::placeholders::_1 ));

  // Subscribe the scene for Leap events on the window
  this->subscribe("LeapLeftEvent",
    std::bind( &BufferCamera::onLeapLeftInput, _camera, std::placeholders::_1 ));
}

void Window::registerCamera(Camera* _camera) {

  // Subscribe the scene for key events on the window
  this->subscribe("ResizeEvent",
    std::bind( &Camera::onResize, _camera, std::placeholders::_1 ));

  // Subscribe the scene for key events on the window
  this->subscribe("KeyEvent",
    std::bind( &Camera::onKeyInput, _camera, std::placeholders::_1 ));

  // Subscribe the scene for mouse events on the window
  this->subscribe("MouseEvent",
    std::bind( &Camera::onMouseInput, _camera, std::placeholders::_1 ));

  // Subscribe the scene for wheel events on the window
  this->subscribe("WheelEvent",
    std::bind( &Camera::onWheelInput, _camera, std::placeholders::_1 ));

  // Subscribe the scene for Leap events on the window
  this->subscribe("LeapEvent",
    std::bind( &Camera::onLeapInput, _camera, std::placeholders::_1 ));

  // Subscribe the scene for Leap events on the window
  this->subscribe("LeapLeftEvent",
    std::bind( &Camera::onLeapLeftInput, _camera, std::placeholders::_1 ));
}

void Window::startEventLoop() {

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(ref)) {
    double _time = glfwGetTime();

    // Notify the subscribers about an update event
    notify(UpdateEvent(_time));

    // Swap front and back buffers
    glfwSwapBuffers(ref);

    // Poll for and process events
    glfwPollEvents();
  }
}

int Window::destroy() {
  glfwTerminate();

  return WINDOW_SUCCESS;
}
