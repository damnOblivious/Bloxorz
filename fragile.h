#include "headers.h"
#include "tiles.h"
#include "3DObject.h"

#ifndef FRAGILE
#define FRAGILE

class fragile:public tiles {
private:
  static Model *tile;

public:
  fragile(float=0.0f,float=0.0f,float=0.0f,grid * = NULL);
  static void initModel();
  void draw();
  void press(int=0);
};

#endif
