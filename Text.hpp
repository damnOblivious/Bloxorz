#include "headers.h"
#include "3DObject.h"

#ifndef TEXT
#define TEXT

using namespace glm;

class Text {

public:

  Model *units, *tens, *hundreds, *lostModel, *wonModel;
  GLint val;

  bool lost, won;

  GLint unitsIndex, tensIndex, hundredsIndex;

  Text(GLchar *path);
  void render();
  void setVal(GLint val);

};


#endif
