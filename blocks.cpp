#include "blocks.h"

int blocks::rotationMagnitude = 3;

blocks::blocks(int x,int y,int z,int xoff,int zoff) {
  cout << x << " " << z << " " << xoff << " " << zoff << endl;
  xCord = (2 * x) - 1;
  zCord = (2 * z) - 1;
  //NOTE x-1 and z-1 in flloing line
  float actualx = float(float(x -1) - xoff) * scalingFactor;
  float actualz = float(float(z -1) - zoff) * scalingFactor;
  cout << actualx << " " << actualz << endl;
  block = new Model("nr/cuboid.obj");
  width = scalingFactor;
  breadth = width;
  height = 2 * width;
  killed = false;
  angle = 0;
  dx = dy = dz = 0;
  glm::mat4 scaling = glm::scale(glm::vec3(scalingFactor,scalingFactor,scalingFactor));
  glm::vec3 translateVec = glm::vec3(actualx, scalingFactor + (scalingFactor/10.0f), actualz);
  glm::mat4 translate = glm::translate (translateVec);
  modelMatrix = translate * scaling;
  positionVector = glm::vec3(glm::mat4(modelMatrix) * glm::vec4(0.0f,0.0f,0.0f,1.0f));
}

void blocks::draw(){
  if(abs(angle) > 0){
    updateModelMatrix();
    updateRotationAngle();
  }
  else if(killed){
    updateModelMatrix();
    positionVector = glm::vec3(glm::mat4(modelMatrix) * glm::vec4(0.0f,0.0f,0.0f,1.0f));
  }

  glm::mat4 MVP = GLMatrices::Matrices.projection * GLMatrices::Matrices.view * modelMatrix;
  glUniformMatrix4fv(GLMatrices::Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  block->render();
}

void blocks::translate(int x,int y, int z, int rotate) {
  if(angle > 0 || killed) {
    return;
  }
  dx = x;
  dy = y;
  dz = z;
  angle = rotate;

  if(dx != 0){
    pointVector = glm::vec3(positionVector.x + (float)dx * (width/2.0f) , positionVector.y - (height/2.0f), positionVector.z);
    translating = glm::translate(pointVector);
    rotationAxis = glm::vec3(0.0f,0.0f,1.0f);
    rotating = glm::rotate(glm::radians(float(dx * -1.0f * rotationMagnitude)),rotationAxis);
    transformMatrix = translating * rotating * glm::inverse(translating);
  }

  if(dz != 0){
    pointVector = glm::vec3(positionVector.x, positionVector.y - (height/2.0f), positionVector.z + (float)dz * (breadth/2.0f));
    translating = glm::translate(pointVector);
    rotationAxis = glm::vec3(1.0f,0.0f,0.0f);
    rotating = glm::rotate(glm::radians(float(dz * rotationMagnitude)),rotationAxis);
    transformMatrix = translating * rotating * glm::inverse(translating);
    }
}

void blocks::updateCoordinatesAndDimensions() {
  if(dx != 0) {
    if((breadth - scalingFactor) < 10e-5){
      xCord = xCord + 3 * dx;
    }
    else {
      xCord = xCord + 2 * dx;
    }
    swap(height,width);
  }

  if(dz != 0){
    if((width - scalingFactor) < 10e-5){
      zCord = zCord + 3 * dz;
    }
    else {
      zCord = zCord + 2 * dz;
    }
    swap(breadth,height);
  }
}

void blocks::updateRotationAngle() {
  angle = angle - rotationMagnitude;
  if(angle <= 0) {
    updateCoordinatesAndDimensions();
    positionVector = glm::vec3(glm::mat4(modelMatrix) * glm::vec4(0.0f,0.0f,0.0f,1.0f));
    changedCoordinates = true;
  }
}

void blocks::togglechangedCoordinates() {
  changedCoordinates = false;
}

bool blocks::getchangedCoordinates() {
  return changedCoordinates;
}

void blocks::updateModelMatrix() {
  modelMatrix = transformMatrix * modelMatrix;
}

glm::vec3 blocks::getBlockCoordinates() {
  return glm::vec3(xCord,yCord,zCord);
}

glm::vec3 blocks::getCenterPosition() {
  return positionVector;
}

glm::vec3 blocks::getBlockDimensions() {
  return glm::vec3(width,height,breadth);
}

void blocks::freeFall() {
  killed = true;
  if((height - 2*scalingFactor) < 10e-5){       //just translate down
    glm::vec3 tvector = glm::vec3(0.0f,-0.05f,0.0f);
    transformMatrix = glm::translate(tvector);
  }
}
