#include "loadShaders.h"
GLuint loadShaders::processShaderData(const char * file_path ,GLenum shaderType){
  // Create the shaders
  GLuint ShaderID = glCreateShader(shaderType);

  // Read the Vertex Shader code from the file
  std::string ShaderCode;
  std::ifstream ShaderStream(file_path, std::ios::in);
  if(ShaderStream.is_open())
  {
    std::string Line = "";
    while(getline(ShaderStream, Line))
    ShaderCode += "\n" + Line;
    ShaderStream.close();
  }

  GLint status = GL_FALSE;
  int InfoLogLength;

  // Compile Vertex Shader
  // printf("Compiling shader : %s\n", file_path);
  char const * SourcePointer = ShaderCode.c_str(); //.c_str() returns a constant string.
  glShaderSource(ShaderID, 1, &SourcePointer , NULL);
  glCompileShader(ShaderID);

  // Check Vertex Shader
  glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &status);
  if(!status){
    glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
    cout << file_path << endl;
    fprintf(stdout, "%s\n", &ShaderErrorMessage[0]);
  }
  return ShaderID;
}

GLuint loadShaders::linkProgram(GLuint VertexShaderID, GLuint FragmentShaderID){
  // Link the program
  // fprintf(stdout, "Linking program\n");
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, VertexShaderID);
  glAttachShader(ProgramID, FragmentShaderID);
  glLinkProgram(ProgramID);

  // Check the program
  GLint status = GL_FALSE;
  int InfoLogLength;

  glGetProgramiv(ProgramID, GL_LINK_STATUS, &status);
  if(!status){
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    fprintf(stdout, "Here:%s\n", &ProgramErrorMessage[0]);
  }
  glDeleteShader(VertexShaderID);
  glDeleteShader(FragmentShaderID);

  return ProgramID;
}
