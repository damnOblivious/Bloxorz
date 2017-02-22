#include "tiles.h"
#include "drawObjects.h"
#include "3DObject.h"
#include "grid.h"

int tiles::rotationMagnitude = 1;

void tiles::setModelMatrix() {
  removed = false;
  rotated = false;
  isGoal = false;
  width = scalingFactor;
  breadth = width;
  height = width/5.0f;
  angle = 0;
  pressed = false;
  glm::mat4 scaling = glm::scale(glm::vec3(scalingFactor,scalingFactor,scalingFactor));
  glm::mat4 rotating = glm::rotate((float)glm::radians(0.0f),glm::vec3(0,0,1));
  glm::mat4 translate = glm::translate (glm::vec3(xCord, yCord, zCord));
  modelMatrix = translate * rotating * scaling;
  positionVector = glm::vec3(glm::mat4(modelMatrix) * glm::vec4(0.0f,0.0f,0.0f,1.0f));
}

void tiles::rotateRight(int dir) {
  if(abs(angle) > 0) {
    return;
  }
  angle = 90;
  pointVector = glm::vec3(positionVector.x + (width/2.0f) , positionVector.y - (float(dir) * (height/2.0f)) , positionVector.z);
  glm::mat4 translating = glm::translate(pointVector);
  rotationAxis = glm::vec3(0.0f,0.0f,1.0f);
  glm::mat4 rotating = glm::rotate(glm::radians(float(dir * rotationMagnitude)),rotationAxis);
  transformMatrix = translating * rotating * glm::inverse(translating);
  swap(height,width);
  rotated = !rotated;
}

void tiles::rotateLeft(int dir) {
  if(abs(angle) > 0) {
    return;
  }
  angle = 90;
  pointVector = glm::vec3(positionVector.x - (width/2.0f) , positionVector.y - (float(dir) * height/2.0f), positionVector.z);
  glm::mat4 translating = glm::translate(pointVector);
  rotationAxis = glm::vec3(0.0f,0.0f,1.0f);
  glm::mat4 rotating = glm::rotate(glm::radians(float(dir * -1.0f * rotationMagnitude)),rotationAxis);
  transformMatrix = translating * rotating * glm::inverse(translating);
  swap(height,width);
  rotated = !rotated;
}

void tiles::rotateForward(int dir) {
  if(abs(angle) > 0) {
    return;
  }
  angle = 90;
  pointVector = glm::vec3(positionVector.x, positionVector.y - (dir * height/2.0f), positionVector.z + (breadth/2.0f));
  glm::mat4 translating = glm::translate(pointVector);
  rotationAxis = glm::vec3(1.0f,0.0f,0.0f);
  glm::mat4 rotating = glm::rotate(glm::radians(float(dir * -1.0f * rotationMagnitude)),rotationAxis);
  transformMatrix = translating * rotating * glm::inverse(translating);
  swap(breadth,height);
  rotated = !rotated;
}


void tiles::rotateBackward(int dir) {
  if(abs(angle) > 0) {
    return;
  }
  angle = 90;
  pointVector = glm::vec3(positionVector.x, positionVector.y - (dir * height/2.0f),  positionVector.z - (breadth/2.0f));
  glm::mat4 translating = glm::translate(pointVector);
  rotationAxis = glm::vec3(1.0f,0.0f,0.0f);
  glm::mat4 rotating = glm::rotate(glm::radians(float(dir * rotationMagnitude)),rotationAxis);
  transformMatrix = translating * rotating * glm::inverse(translating);
  swap(breadth,height);
  rotated = !rotated;
}

void tiles::updateRotationAngle() {
  if(angle > 0){
    angle = angle - rotationMagnitude;
  }
  else {
    angle = angle + rotationMagnitude;
  }
  if(abs(angle) <= 0) {
    positionVector = glm::vec3(glm::mat4(modelMatrix) * glm::vec4(0.0f,0.0f,0.0f,1.0f));
  }
}

void tiles::updateModelMatrix() {
  modelMatrix = transformMatrix * modelMatrix;
}

void tiles::removeTile() {
  transformMatrix = glm::translate(glm::vec3(0.0f,-0.2f,0.0f));
  removed = true;
}
bool tiles::isrotated() {
  return rotated;
}

bool tiles::reachedGoal() {
  return isGoal;
}
