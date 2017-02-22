#include "drawObjects.h"
#include "3DObject.h"

void drawObjects::draw3DObject(struct VAO* vao, int indicesSize) {
  glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
  glPolygonMode (GL_FRONT_AND_BACK, vao->FillMode);
  glBindVertexArray (vao->VertexArrayID);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glDrawElements(vao->PrimitiveMode, indicesSize, GL_UNSIGNED_INT, 0);
}

VAO* drawObjects::create3DObject(GLenum primitive_mode, vector<vertexInfo> info, vector<GLuint> &indicesOrder, GLenum fill_mode) {
  VAO* vao = new VAO;
  vao->PrimitiveMode = primitive_mode;
  vao->NumVertices = info.size();
  vao->FillMode = fill_mode;
  /**************************Generate required buffers*************************/
  glGenVertexArrays(1, &(vao->VertexArrayID));
  glGenBuffers (1, &(vao->VBO));
  glGenBuffers(1, &(vao->EBO));
  /**************************Bind buffers to send data*************************/
  glBindVertexArray (vao->VertexArrayID);
  glBindBuffer (GL_ARRAY_BUFFER, vao->VBO);
  glBufferData (GL_ARRAY_BUFFER, info.size() * sizeof(vertexInfo), info.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesOrder.size() * sizeof(GLuint), indicesOrder.data(), GL_STATIC_DRAW);
  /**************************instruct vertexAttribPointer about data format*************************/
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertexInfo), (GLvoid*)offsetof(vertexInfo, position));
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertexInfo), (GLvoid*)offsetof(vertexInfo, color));
  return vao;
}
