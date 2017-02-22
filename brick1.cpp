#include "brick1.h"
#include "3DObject.h"

Model * brick1::tile = NULL;

brick1::brick1(float x,float y,float z){
  xCord = x;
  yCord = y;
  zCord = z;
  setModelMatrix();
}

void brick1::initModel() {
  tile = new Model("nr/brick1.obj");
}

void brick1::draw() {
  if(abs(angle) > 0) {
    updateModelMatrix();
    updateRotationAngle();
  }
  if(removed) {
    updateModelMatrix();
  }

  glm::mat4 MVP = GLMatrices::Matrices.projection * GLMatrices::Matrices.view * modelMatrix;
  glUniformMatrix4fv(GLMatrices::Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  tile->render();
}

void brick1::press(int heavypress) {

}
