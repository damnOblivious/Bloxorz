#include "reshapeWindow.h"

void reshapeWindow::reshapeWindowFunction (GLFWwindow* window, int width, int height) {
  int fbwidth = width;
  int fbheight = height;
  glfwGetFramebufferSize(window, &fbwidth, &fbheight);
  GLfloat fov = 90.0f;
  glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);
  GLMatrices::Matrices.projection = glm::perspective(fov/2, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1f, 500.0f);
}
