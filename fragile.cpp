#include "fragile.h"
#include "3DObject.h"
#include "grid.h"

Model * fragile::tile = NULL;

fragile::fragile(float x,float y,float z, grid * currGrid){
  xCord = x;
  yCord = y;
  zCord = z;
  myGrid = currGrid;
  setModelMatrix();
}

void fragile::initModel() {
  tile = new Model("nr/brick1.obj");
}

void fragile::draw() {
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
void fragile::press(int heavypress) {
  if(heavypress == 0) {
    return;
  }
  x = (xCord - myGrid->getxoffset())/scalingFactor + 1;         //NOTE +1 factor
  z = (zCord - myGrid->getzoffset())/scalingFactor + 1;         //NOTE +1 factor
  std::cout << x << " m fragile " << z << std::endl;
  myGrid->removeTile(x,z);
}
