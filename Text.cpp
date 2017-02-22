#include "Text.hpp"


Text::Text(GLchar *path)
{
  this->units = new Model(path);
  this->tens = new Model(path);
  this->hundreds = new Model(path);

  this->wonModel = new Model("nr/won.obj");
  this->lostModel = new Model("nr/lost.obj");

  this->wonModel->rotateAround(vec3(1.0f, 0.0f, 0.0f), 90);
  this->wonModel->moveTo(vec3(10.24f, 7.68f, -1.0f));
  this->lostModel->rotateAround(vec3(1.0f, 0.0f, 0.0f), 90);
  this->lostModel->moveTo(vec3(10.24f, 7.68f, -1.0f));

  this->unitsIndex = 0;
  this->tensIndex = 0;
  this->hundredsIndex = 0;

  this->val = 0;
  this->won = false;
  this->lost = false;

  this->tens->rotateAround(vec3(1.0f, 0.0f, 0.0f), 90);
  this->tens->moveTo(vec3(1.0f, 7.0f, -1.0f));

  this->units->rotateAround(vec3(1.0f, 0.0f, 0.0f), 90);
  this->units->moveTo(vec3(1.5f, 7.0f, -1.0f));

  this->hundreds->rotateAround(vec3(1.0f, 0.0f, 0.0f), 90);
  this->hundreds->moveTo(vec3(0.5f, 7.0f, -1.0f));
}

void Text::setVal(GLint val)
{
  GLint units = val % 10;
  GLint tens = (val / 10) % 10;
  GLint hundreds = (val / 100) % 10;

  this->val = val;

  this->unitsIndex = units;
  this->tensIndex = tens;
  this->hundredsIndex = hundreds;
}

void Text::render()
{

  if(this->won == true)
    this->wonModel->render();
  else if(this->lost == true)
    this->lostModel->render();

  for(GLint i=0;i<10;i++)
  {
    Mesh *mesh = this->units->meshes[i];

    GLint id = glGetUniformLocation(programID, "MVP");

    glm::mat4 MVP = glm::ortho(0.0f, 10.24f, 0.0f, 7.68f, 0.1f, 100.0f) * this->units->modelMatrix;
    glUniformMatrix4fv(id, 1, GL_FALSE, &MVP[0][0]);
    /*
    if(mesh->name == to_string(this->unitsIndex));
      this->units->meshes[i]->render(this->units->modelMatrix);
      */

    MVP = glm::ortho(0.0f, 10.24f, 0.0f, 7.68f, 0.1f, 100.0f) * this->tens->modelMatrix;
    glUniformMatrix4fv(id, 1, GL_FALSE, &MVP[0][0]);
    mesh = this->tens->meshes[i];
    if(mesh->name == to_string(this->tensIndex))
      this->tens->meshes[i]->render(this->tens->modelMatrix);

    MVP = glm::ortho(0.0f, 10.24f, 0.0f, 7.68f, 0.1f, 100.0f) * this->hundreds->modelMatrix;
    glUniformMatrix4fv(id, 1, GL_FALSE, &MVP[0][0]);
    mesh = this->hundreds->meshes[i];
    if(mesh->name == to_string(this->hundredsIndex))
      this->hundreds->meshes[i]->render(this->hundreds->modelMatrix);
  }

}
