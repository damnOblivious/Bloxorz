#include "headers.h"
#include "tiles.h"
#include "3DObject.h"

#ifndef BRICK1
#define BRICK1

class brick1:public tiles {
private:
  static Model *tile;

public:
  brick1(float=0.0f,float=0.0f,float=0.0f);
  static void initModel();
  void draw();
  void press(int=0);
};

#endif
