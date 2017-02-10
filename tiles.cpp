#include "tiles.h"
#include "drawObjects.h"

float blocks::speed = 0.01f;
blocks::blocks(float x, int randColor) {
  xCord = x;
  yCord = 0.0f;
  color = randColor;
  vector<GLfloat> colorVec = {1,0,0};

  vector<glm::vec4> vertices(8);
  vertices[0] = glm::vec4{ 1.0f,  1.0f,  1.0f, 1.0f};
  vertices[1] = glm::vec4{-1.0f,  1.0f,  1.0f, 1.0f};
  vertices[2] = glm::vec4{-1.0f, -1.0f,  1.0f, 1.0f};
  vertices[3] = glm::vec4{ 1.0f, -1.0f,  1.0f, 1.0f};
  vertices[4] = glm::vec4{ 1.0f,  1.0f, -1.0f, 1.0f};
  vertices[5] = glm::vec4{-1.0f,  1.0f, -1.0f, 1.0f};
  vertices[6] = glm::vec4{-1.0f, -1.0f, -1.0f, 1.0f};
  vertices[7] = glm::vec4{ 1.0f, -1.0f, -1.0f, 1.0f};

  vertexInfo tempInfo;

  for(int i = 0; i < 8 ; ++i) {
    tempInfo.position = glm::vec4(vertices[i]);
    tempInfo.color = glm::vec3{1,0,0};
    info.push_back(tempInfo);
  }

  indicesOrder = {
    0,1,2,2,3,0,
    4,5,6,6,7,4,
    0,3,7,7,4,0,
    1,2,6,6,5,1,
    0,1,5,5,4,0,
    3,2,6,6,7,3
  };
  // create3DObject creates and returns a handle to a VAO that can be used later
  block = drawObjects::create3DObject(GL_TRIANGLES, info, indicesOrder, GL_FILL);
}

float blocks::getxCord() {
  return xCord;
}
float blocks::getyCord() {
  return yCord;
}
int blocks::getColor() {
  return color;
}

void blocks::draw() {
  GLMatrices::Matrices.model = glm::mat4(1.0f);
  glm::mat4 scaling = glm::scale(glm::vec3(0.5f,0.1f,0.1f));
  glm::mat4 translate = glm::translate (glm::vec3(0.0f, 0.0f, 0.0f));
  GLMatrices::Matrices.model = translate;
  glm::mat4 MVP = GLMatrices::Matrices.projection * GLMatrices::Matrices.view *GLMatrices::Matrices.model;
  glUniformMatrix4fv(GLMatrices::Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  drawObjects::draw3DObject(block,indicesOrder.size());
}
