#include "brick2.h"
#include "3DObject.h"

Model * brick2::tile = NULL;

void brick2::initModel() {
  tile = new Model("nr/brick2.obj");
}

brick2::brick2(float x,float y, float z, grid * currGrid){
  xCord = x;
  yCord = y;
  zCord = z;
  myGrid = currGrid;
  setModelMatrix();
}
void brick2::draw() {
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
void brick2::press(int heavypress) {

}
