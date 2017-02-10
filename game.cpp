#include "headers.h"
#include "basicSetup.h"
#include "reshapeWindow.h"
#include "camera.h"
#include "tiles.h"

double last_update_time, current_time;
vector<blocks *> tileCollection;

float delay_time = 0.5f;
float bullet_delay_time = 0.0f;
bool gameOver;

double cursor_x, cursor_y,currentcursor_x, currentcursor_y,cannon_x,cannon_y;
int window_width = 600;

/*************************getting co-ordinates of cursor****************************/

void getOriginalCoordinates(GLFWwindow * window, double * x, double * y) {
  glfwGetCursorPos(window, x, y);
  *x = (*x)/window_width * 2 - 1.0f;
  *y =  1.0f - (*y)/window_width * 2;
  // cout << *x <<  " by * " << *y << endl;
  glm::vec3 v1 = glm::vec3(GLMatrices::Matrices.inverseVP * glm::vec4((float)(*x),(float)(*y),0.0f,1.0f));
  *x = v1.x;
  *y = v1.y;
  // cout << *x <<  " by 1*1 " << *y << endl;
}

/**********************eventHandler Functions********************************************/
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (action == GLFW_RELEASE) {
    switch (key) {
      case GLFW_KEY_A:
      break;
      case GLFW_KEY_D:
      break;
      case GLFW_KEY_F:
      break;
    }
  }
  else if (action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_ESCAPE:
      gameOver = true;
      // basicSetup::quit(window);
      break;
      default:
      break;
    }
  }
  else if (action == GLFW_REPEAT) {
    switch (key) {
      case GLFW_KEY_UP:
      reshapeWindow::zoom(-0.03f);
      break;
      case GLFW_KEY_DOWN:
      reshapeWindow::zoom(0.03f);
      break;
    }
  }
}

void mouseButton (GLFWwindow* window, int button, int action, int mods) {
  switch (button) {
    case GLFW_MOUSE_BUTTON_RIGHT:
    if(action == GLFW_PRESS) {
    }
    else if (action == GLFW_RELEASE) {
    }
    break;
    default:
    break;
  }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
  reshapeWindow::zoom(0.03 * yoffset);
}

/**********************************************************************/


void displayObjects() {
  for(auto block: tileCollection){
    // std::cout << "draw" << std::endl;
    block->draw();
  }
}

int main()
{
  basicSetup setup;
  GLFWwindow* window = setup.initGLFW();

  setup.initGL(window);
  last_update_time = glfwGetTime();
  gameOver = false;
  tileCollection.push_back(new blocks(0,0));
  while(gameOver == false){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    current_time = glfwGetTime();
    if ((current_time - last_update_time) >= delay_time) {
    }
    displayObjects();
    glfwSwapBuffers(window);
    glfwPollEvents();
  };

  cout << "Game Over" << endl << "Your Score:"  << endl;
  glfwTerminate();
  exit(0);
}
