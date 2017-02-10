#include "camera.h"

float camera::xCord = 0.0f;
float camera::yCord = 0.0f;

float camera::cameraRotAngle;
camera::camera(float initialRotAngle){
  camera::cameraRotAngle = initialRotAngle;
}

void camera::panAlongX(float displacement) {
  xCord = xCord - displacement;
  GLMatrices::Matrices.view = glm::lookAt(glm::vec3(xCord,yCord,3), glm::vec3(xCord,yCord,0), glm::vec3(0,1,0));
  GLMatrices::Matrices.inverseVP = glm::inverse(GLMatrices::Matrices.projection * GLMatrices::Matrices.view);
}


void camera::panAlongY(float displacement) {
  yCord = yCord - displacement;
  GLMatrices::Matrices.view = glm::lookAt(glm::vec3(xCord,yCord,3), glm::vec3(xCord,yCord,0), glm::vec3(0,1,0));
  GLMatrices::Matrices.inverseVP = glm::inverse(GLMatrices::Matrices.projection * GLMatrices::Matrices.view);
}

void camera::setCameraPosition() {
  // Eye - Location of camera. Don't change unless you are sure!!
  glm::vec3 eye ( 5*cos(camera::cameraRotAngle*M_PI/180.0f), 0, 5*sin(camera::cameraRotAngle*M_PI/180.0f) );
  // Target - Where is the camera looking at.  Don't change unless you are sure!!
  // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
  glm::vec3 target (0, 0, 0);
  glm::vec3 up (0, 1, 0);

  // Compute Camera matrix (view)
  // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
  GLMatrices::Matrices.view = glm::lookAt(glm::vec3(-3,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
  GLMatrices::Matrices.inverseVP = glm::inverse(GLMatrices::Matrices.projection * GLMatrices::Matrices.view);
  }
