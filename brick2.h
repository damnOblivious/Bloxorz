#include "headers.h"
#include "tiles.h"
#include "3DObject.h"

#ifndef BRICK2
#define BRICK2

class brick2:public tiles {
private:
  static Model *tile;

public:
  brick2(float,float,float,grid *);
  static void initModel();
  void draw();
  void press(int=0);
};

#endif
