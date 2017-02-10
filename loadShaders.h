#include "headers.h"

#ifndef LOAD_SHADERS
#define LOAD_SHADERS

class loadShaders {
public:
  static GLuint processShaderData(const char * file_path ,GLenum shaderType);
  static GLuint linkProgram(GLuint VertexShaderID, GLuint FragmentShaderID);
};

#endif
