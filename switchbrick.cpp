#include "switchbrick.h"
#include "3DObject.h"

Model * switchbrick::tile = NULL;

switchbrick::switchbrick(float x,float y,float z, vector<string> v,grid * currGrid):changes(v){
  xCord = x;
  yCord = y;
  zCord = z;
  myGrid = currGrid;
  setModelMatrix();
}

void switchbrick::initModel() {
  tile = new Model("nr/switch.obj");
}

void switchbrick::draw() {
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

void switchbrick::press(int heavypress) {
  if(heavypress == 0){        //NOTE take care of the time
    return;
  }
  if(!pressed) {
    pressed = true;
    for ( int i = 1;i < changes.size();){
      type = changes[i];
      if(type == "toggle") {
        direction = changes[i+1];
        xindex = stoi(changes[i+2]);
        zindex = stoi(changes[i+3]);
        operateOn = myGrid->getTile(xindex,zindex);
        if(direction == "left") {
          operateOn->rotateLeft(1);
        }
        else if(direction == "right") {
          operateOn->rotateRight(1);
        }
        else if(direction == "forward"){
          operateOn->rotateForward(1);
        }
        else if(direction == "backward"){
          operateOn->rotateBackward(1);
        }
        i = i + 4;
      }
      else if(type == "remove") {
        xindex = stoi(changes[i+1]);
        zindex = stoi(changes[i+2]);
        myGrid->removeTile(xindex,zindex);
        i = i + 3;
      }
    }
  }
  else {
    pressed = false;
    for ( int i = 1;i < changes.size();){
      type = changes[i];
      if(type == "toggle") {
        direction = changes[i+1];
        xindex = stoi(changes[i+2]);
        zindex = stoi(changes[i+3]);
        operateOn = myGrid->getTile(xindex,zindex);
        if(direction == "left") {
          operateOn->rotateLeft(-1);
        }
        else if(direction == "right") {
          operateOn->rotateRight(-1);
        }
        else if(direction == "forward"){
          operateOn->rotateForward(-1);
        }
        else if(direction == "backward"){
          operateOn->rotateBackward(-1);
        }
        i = i + 4;
      }
      else if(type == "remove") {
        i = i + 3;
        continue;
        // xindex = stoi(changes[i+1]);
        // zindex = stoi(changes[i+2]);
        // myGrid->setTile(xindex,zindex);
      }
    }
  }
}
