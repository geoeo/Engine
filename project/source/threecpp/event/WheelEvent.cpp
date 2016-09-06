#include "WheelEvent.h"

WheelEvent::WheelEvent(GLFWwindow* window, double _dx, double _dy) {
  dx = _dx;
  dy = _dy;

  // Get window dimensions
  glfwGetWindowSize(window, &windowWidth, &windowHeight);

  // Get the Cursor position
  glfwGetCursorPos(window, &xpos, &ypos);

  // Get Mouse button status
  leftDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
  middleDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
  rightDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

WheelEvent::~WheelEvent() {

}