#include "headers.h"

#ifndef CAMERA
#define CAMERA

class camera {
private:
  static float cameraRotAngle;
  static float xCord;
  static float yCord;

public:
  camera(float=90.0f);
  static void panAlongX(float displacement);
  static void panAlongY(float displacement);
  static void setCameraPosition();
  float getCameraRotAngle();
  void setCameraRotAngle();
};

#endif
