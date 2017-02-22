#include "headers.h"
#include "tiles.h"
#include "3DObject.h"

#ifndef GOALTILE
#define GOALTILE

class goaltile:public tiles {
private:
  static Model *tile;

public:
  goaltile(float=0.0f,float=0.0f,float=0.0f,grid * = NULL);
  static void initModel();
  void draw();
  void press(int=0);
};

#endif
