#include "goaltile.h"
#include "3DObject.h"
#include "grid.h"

Model * goaltile::tile = NULL;

goaltile::goaltile(float x,float y,float z, grid * currGrid){
  xCord = x;
  yCord = y;
  zCord = z;
  myGrid = currGrid;
  setModelMatrix();
  isGoal = true;
}

void goaltile::initModel() {
  tile = new Model("nr/goal.obj");
}

void goaltile::draw() {
  if(abs(angle) > 0) {
    updateModelMatrix();
    updateRotationAngle();
  }
  glm::mat4 MVP = GLMatrices::Matrices.projection * GLMatrices::Matrices.view * modelMatrix;
  glUniformMatrix4fv(GLMatrices::Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  tile->render();
}

void goaltile::press(int heavypress) {
  if(heavypress == 0) {
    return;
  }
  x = (xCord - myGrid->getxoffset())/scalingFactor + 1;         //NOTE +1 factor
  z = (zCord - myGrid->getzoffset())/scalingFactor + 1;         //NOTE +1 factor
  std::cout << " VICTORY " << std::endl;
  myGrid->removeTile(x,z);
}
