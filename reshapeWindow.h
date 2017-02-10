#include "headers.h"

#ifndef RESHAPE_WINDOW
#define RESHAPE_WINDOW

class reshapeWindow {
private:
  static float limit;
public:
  static void zoom(float sign);
  static void reshapeWindowFunction (GLFWwindow* window, int width, int height);
};

#endif
