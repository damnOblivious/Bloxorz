#include "reshapeWindow.h"

float reshapeWindow::limit = 4.0f;

void reshapeWindow::zoom(float sign) {
  limit = min(4.0f,limit + sign);
  GLMatrices::Matrices.projection = glm::ortho(-1.0f*limit, limit, -1.0f*limit, limit, 0.1f, 500.0f);
  GLMatrices::Matrices.inverseVP = glm::inverse(GLMatrices::Matrices.projection * GLMatrices::Matrices.view);
  // GLMatrices::Matrices.inverseVP = glm::inverse(GLMatrices::Matrices.view * GLMatrices::Matrices.projection);
}

void reshapeWindow::reshapeWindowFunction (GLFWwindow* window, int width, int height) {
  int fbwidth = width;
  int fbheight = height;
  // sets the viewport of openGL renderer
  glfwGetFramebufferSize(window, &fbwidth, &fbheight);
  // limit = initialLimit;
  GLfloat fov = 90.0f;
  glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);

  // set the projection matrix as perspective
  /* glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1, 500.0); */
  // Store the projection matrix in a variable for future use
  // Perspective projection for 3D views
  // Matrices.projection = glm::perspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1f, 500.0f);

  // Ortho projection for 2D views
  // GLMatrices::Matrices.projection = glm::ortho(-1.0f*limit, limit, -1.0f*limit, limit, 0.1f, 500.0f);
  GLMatrices::Matrices.projection = glm::perspective(45.0f, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1f, 500.0f);
}
