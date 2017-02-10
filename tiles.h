#include "headers.h"

#ifndef BLOCKS
#define BLOCKS

class blocks {
private:
  VAO* block;
  vector<vertexInfo> info;
  vector<GLuint> indicesOrder;
  float xCord;
  float yCord;
  int color;
  static float speed;

public:
  blocks(float,int);
  void draw();
  void translate(int displacement);
  float getxCord();
  float getyCord();
  int getColor();
};

#endif
