#include "headers.h"

#ifndef DRAW_OBJECT
#define DRAW_OBJECT

class drawObjects {
public:
  static VAO* create3DObject(GLenum primitive_mode, vector<vertexInfo> info, vector<GLuint> &indicesOrder, GLenum fill_mode);
  static void draw3DObject(struct VAO* vao, int indicesSize);
};

#endif
