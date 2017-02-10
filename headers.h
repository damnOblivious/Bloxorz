/*******************************Header Files & Macros******************************/
#ifndef HEADERS_HPP

#define HEADERS_HPP
#include <mpg123.h>
#include <ao/ao.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <list>
#include <time.h>       /* time */
#include <cstdlib>      /*random function*/
#include <math.h>       /* sqrt */
// #include <mpg123.h>
// #include <ao/ao.h>

using namespace std;

/*****************************Varibales*****************************************/
#define GLM_FORCE_RADIANS
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods);
void keyboardChar (GLFWwindow* window, unsigned int key);
void mouseButton (GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

typedef struct VAO {
  GLuint VertexArrayID;
  GLuint VBO;
  GLuint EBO;
  GLenum PrimitiveMode;
  GLenum FillMode;
  int NumVertices;
}VAO;

typedef struct vertexInfo {
  glm::vec4 position;
  glm::vec3 color;
}vertexInfo;


struct GLMatrices {
  glm::mat4 projection;
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 inverseVP;
  GLuint MatrixID;
  static struct GLMatrices Matrices;
};
#endif
