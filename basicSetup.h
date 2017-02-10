#include "headers.h"

#ifndef BASICSETUP
#define BASICSETUP

class basicSetup {
private:
  int width ;
  int height;
public:
  basicSetup(int=600, int=600);
  static void quit(GLFWwindow * window);
  void setWidth(int newWidth);
  void setHeight(int newHeight);
  GLFWwindow* initGLFW ();
  void initGL(GLFWwindow* window);
};

#endif
