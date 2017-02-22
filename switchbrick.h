#include "headers.h"
#include "tiles.h"
#include "3DObject.h"

#ifndef SWITCHBRICK
#define SWITCHBRICK

class switchbrick:public tiles {
private:
  static Model *tile;
  vector <string> changes;
  string type,direction;
  int xindex,zindex;
  tiles * operateOn;

public:
  switchbrick(float=0.0f,float=0.0f,float=0.0f,vector<string> = {"switch"}, grid * = NULL);
  static void initModel();
  void draw();
  void press(int=0);
};

#endif
