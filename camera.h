#include "headers.h"
#include "blocks.h"
#ifndef CAMERA
#define CAMERA

class camera {
private:
  blocks * myBlock;
  float cameraRotAngle;
  float xCord, yCord;
  glm::vec3 eye, target, up, blockCenter, blockDimensions;

public:
  camera(float,float,blocks * = NULL);
  void setNormalView(float,float);
  void setTopView(float,float);
  void setFirstPersonView(int);
  void setFollowView();
  void setHeliView(float,float,float,float);
  void setViewMatrix();
};

#endif
