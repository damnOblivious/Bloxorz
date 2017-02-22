#include "headers.h"
#include "3DObject.h"

#ifndef BLOCKS
#define BLOCKS

class blocks {
private:
  Model * block;
  int xCord, yCord, zCord;
  int dx, dy, dz;
  int angle;
  bool killed;
  static int rotationMagnitude;
  float height,width,breadth;
  glm::mat4 modelMatrix,translating,rotating,transformMatrix;
  glm::vec3 positionVector,pointVector,rotationAxis;
  glm::vec2 coordinates;
  bool changedCoordinates;

public:
  blocks(int,int,int,int,int);
  void draw();
  void translate(int,int,int,int);
  glm::vec3 getBlockCoordinates();
  glm::vec3 getCenterPosition();
  glm::vec3 getBlockDimensions();
  void freeFall();
  bool getchangedCoordinates();
  void togglechangedCoordinates();
  void updateCoordinatesAndDimensions();
  void updateModelMatrix();
  void updateRotationAngle();
};

#endif
