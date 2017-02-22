#include "headers.h"
#include "grid.h"
#ifndef TILES
#define TILES

class tiles {
protected:
  float xCord, yCord, zCord;
  int color;
  bool removed,rotated,isGoal;
  glm::mat4 modelMatrix,transformMatrix;
  glm::vec3 positionVector,pointVector,rotationAxis;
  float height,width,breadth;
  int angle;
  int z, x;
  bool pressed;
  grid * myGrid;


public:
  static void initModel();
  static int rotationMagnitude;
  void setModelMatrix();
  virtual void draw()=0;
  void rotateAbt(int,int,int,int);
  void updateCoordinatesAndDimensions();
  void updateModelMatrix();
  void updateRotationAngle();
  virtual void press(int=0)=0;
  void rotateRight(int=1);
  void rotateLeft(int=1);
  void rotateForward(int=1);
  void rotateBackward(int=1);
  void removeTile();
  bool isrotated();
  bool reachedGoal();
};

#endif
