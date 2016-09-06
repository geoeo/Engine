#include "MouseEvent.h"

MouseEvent::MouseEvent(GLFWwindow* window, int _button, int _action, int _mod) {
  button = _button;
  action = _action;
  mod = _mod;

  // Get window dimensions
  glfwGetWindowSize(window, &windowWidth, &windowHeight);

  // Get the Cursor position
  glfwGetCursorPos(window, &xpos, &ypos);

  // Get Mouse button status
  leftDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
  middleDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
  rightDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

MouseEvent::~MouseEvent() {

}