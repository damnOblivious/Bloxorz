#include "drawObjects.h"

void drawObjects::draw3DObject(struct VAO* vao, int indicesSize) {
  // Change the Fill Mode for this object
  glPolygonMode (GL_FRONT_AND_BACK, vao->FillMode);

  // Bind the VAO to use
  glBindVertexArray (vao->VertexArrayID);

  // Enable Vertex Attribute 0 - 3d Vertices
  glEnableVertexAttribArray(0);
  // Bind the VBO to use
  //glBindBuffer(GL_ARRAY_BUFFER, vao->VertexBuffer);

  // Enable Vertex Attribute 1 - Color
  glEnableVertexAttribArray(1);
  // Bind the VBO to use
  //glBindBuffer(GL_ARRAY_BUFFER, vao->ColorBuffer);

  // Draw the geometry !
  glDrawElements(vao->PrimitiveMode, indicesSize, GL_UNSIGNED_INT, 0);
  // std::cout << "draw" << std::endl;
}

VAO* drawObjects::create3DObject(GLenum primitive_mode, vector<vertexInfo> info, vector<GLuint> &indicesOrder, GLenum fill_mode) {
  VAO* vao = new VAO;
  vao->PrimitiveMode = primitive_mode;
  vao->NumVertices = info.size();
  vao->FillMode = fill_mode;

  glGenVertexArrays(1, &(vao->VertexArrayID));
  glGenBuffers (1, &(vao->VBO));
  glGenBuffers(1, &(vao->EBO));
  glBindVertexArray (vao->VertexArrayID); // Bind the VAO

  glBindBuffer (GL_ARRAY_BUFFER, vao->VBO);
  glBufferData (GL_ARRAY_BUFFER, info.size() * sizeof(vertexInfo), info.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao->EBO);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesOrder.size() * sizeof(GLuint), indicesOrder.data(), GL_STATIC_DRAW);


  glVertexAttribPointer(
    0, 4, GL_FLOAT, GL_FALSE, sizeof(vertexInfo), (GLvoid*)offsetof(vertexInfo, position)
  );

  glVertexAttribPointer(
    1, 3, GL_FLOAT, GL_FALSE, sizeof(vertexInfo), (GLvoid*)offsetof(vertexInfo, color)
  );
  return vao;
}
