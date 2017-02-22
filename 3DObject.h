#include "headers.h"

#ifndef OBJECT
#define OBJECT

using namespace glm;

typedef struct Vertex {
  vec3 position;
  vec3 normal;
  vec2 texCoords;
} Vertex;

typedef struct Texture {
  GLint id;
  std::string type;
  aiString path;
} Texture;



class Mesh {

public:
  GLuint VAO, VBO, EBO;

  vector<Vertex> vertices;
  vector<GLuint> indices;
  vector<Texture> textures;
  string name;
  vec3 position;
  mat4 modelMatrix;

  Mesh(vector<Vertex> &vertices, vector<GLuint> indices, vector<Texture> textures, const GLchar *name);
  Mesh(Mesh *mesh);
  Mesh();

  void setupMesh();
  void moveTo(vec3 position);
  void rotateAround(vec3 axis, GLfloat angle);
  void render(mat4 parentModelMatrix);

};

class Model {

public:
  const aiScene * scene;
  mat4 modelMatrix, rotateMatrix, translateMatrix;
  vector<Mesh*> meshes;
  vector<Texture> textures_loaded;

  Model(GLchar* path);

  void render();
  Mesh* cloneMesh(Mesh* mesh, vec3 position);
  void loadModel(string path);

  void genMeshes(aiNode* rootNode);
  void loadTextures(vector<Texture> &textures, aiMaterial* mat, aiTextureType type, string typeName);
  GLuint getTexture(const char * filename);
  Mesh* genMeshObj(aiMesh* mesh);

  void resetModelMatrix();
  void moveTo(vec3 position);
  void rotateAround(vec3 axis, GLfloat angle);

};


#endif
