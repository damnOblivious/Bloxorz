#include "headers.h"
#include "basicSetup.h"
#include "reshapeWindow.h"
#include "camera.h"
#include "tiles.h"
#include "brick1.h"
#include "brick2.h"
#include "switchbrick.h"
#include "fragile.h"
#include "grid.h"
#include "blocks.h"
#include "goaltile.h"
#include "Text.hpp"

#define BITS 8

vector<vector<tiles *>> * tileCollection;
blocks * block;
grid * grid1;
camera * cam;
Text *score;

double last_update_time, current_time;
float delay_time = 2.5f;
bool gameOver;
int grid_breadth, grid_length, xoffset, zoffset;
float grid_center_x, grid_center_z;
tiles *tile1, *tile2;
string tile1_type, tile2_type;
int xCord,yCord,zCord;
int moves = 0;

int window_width = 1150, window_height = 650;

float scalingFactor = 0.5f;
int level = 0;
bool updateLevel;

bool fpv = false ,heliView = false, tv = true, trv = false, followView = false;
int firstPersonAngle = 0;       //0 - see in +x direction
float block_x,block_z;
float heliZoomFactor = 4.0f,heliRotationAngle = 0.0f;
bool draggedRotate = false;
double cursor_x,cursor_y,currentcursor_x,	currentcursor_y;


/**********************eventHandler Functions********************************************/
void updateFirstPersonAngle(int d) {
  firstPersonAngle = (firstPersonAngle + d + 360) % 360;
}

void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods){
  if (action == GLFW_RELEASE) {
    switch (key) {
      case GLFW_KEY_UP:
      block->translate(0,0,-1,90);
      break;
      case GLFW_KEY_DOWN:
      block->translate(0,0,1,90);
      break;
      case GLFW_KEY_LEFT:
      block->translate(-1,0,0,90);
      break;
      case GLFW_KEY_RIGHT:
      block->translate(1,0,0,90);
      break;

      case GLFW_KEY_B:          //follow cam
      followView = true;
      heliView = false;
      fpv = false;
      cam->setHeliView(grid_center_x,grid_center_z,heliRotationAngle,heliZoomFactor);
      break;
      case GLFW_KEY_H:
      heliView = true;
      followView = false;
      fpv = false;
      cam->setHeliView(grid_center_x,grid_center_z,heliRotationAngle,heliZoomFactor);
      break;

                                /*HELI CAMERA VIEW*/
      case GLFW_KEY_R:          //rotate helicam
      if(heliView)
        heliRotationAngle = heliRotationAngle + 1.0f;
      break;
      case GLFW_KEY_X:          //zoomIn helicam
      if(heliView)
        heliZoomFactor = heliZoomFactor + 1.0f;
      break;
      case GLFW_KEY_Z:          //zoomOut helicam
      if(heliView)
        heliZoomFactor = heliZoomFactor - 1.0f;
      break;
                                /*HELI CAMERA VIEW*/

                                /*TOWER CAMERA VIEW*/
      case GLFW_KEY_T:
      followView = false;
      fpv = false;
      heliView = false;
      cam->setTopView(grid_center_x,grid_center_z);
      break;

      case GLFW_KEY_N:
      followView = false;
      heliView = false;
      fpv = false;
      cam->setNormalView(grid_center_x,grid_center_z);
      break;
                                      /*FIRST PERSON VIEW*/
      case GLFW_KEY_F:
      followView = false;
      heliView = false;
      fpv = true;
      firstPersonAngle = 0;       //0 - see in +x direction
      break;
      case GLFW_KEY_W:
      if(fpv) {
        updateFirstPersonAngle(0);
      }
      break;
      case GLFW_KEY_S:
      if(fpv) {
        updateFirstPersonAngle(180);
      }
      break;
      case GLFW_KEY_D:
      if(fpv) {
        updateFirstPersonAngle(270);
      }
      break;
      case GLFW_KEY_A:
      if(fpv) {
        updateFirstPersonAngle(90);
      }
      break;
                              /*FIRST PERSON VIEW*/
    }
  }
  else if (action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_ESCAPE:
      gameOver = true;
      break;
      default:
      break;
    }
  }
  else if (action == GLFW_REPEAT) {
    switch (key) {
    }
  }
}

void mouseButton (GLFWwindow* window, int button, int action, int mods) {
  switch (button) {
    case GLFW_MOUSE_BUTTON_RIGHT:
    if(heliView){
      if(action == GLFW_PRESS) {
        glfwGetCursorPos(window, &cursor_x, &cursor_y);
        draggedRotate = true;
      }
      if (action == GLFW_RELEASE){
        draggedRotate = false;
      }
    }
    break;
    default:
    break;
  }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
  heliZoomFactor = heliZoomFactor + yoffset;
}

/**********************************************************************/

void checkFall() {
  glm::vec3 blockPos = block->getBlockCoordinates();
  xCord = blockPos.x;
  yCord = blockPos.y;
  zCord = blockPos.z;

  if( (xCord&1) && (zCord&1) ) {                         //completely on one tile
    tile1_type = grid1->getTileColor((xCord + 1)/2, (zCord + 1)/2);
    if( tile1_type == "NULL" ) {
      block->freeFall();
    }
    else {
      tile1 = grid1->getTile((xCord + 1)/2, (zCord + 1)/2);
      if(tile1->isrotated() == true) {
        block->freeFall();
      }
      if(tile1->reachedGoal() == true) {
        block->freeFall();
        updateLevel = true;
        std::cout << "SCORE = 1000" << std::endl;
        last_update_time = glfwGetTime();
      }
      else {
        tile1->press(1);
      }
    }
  }

  else if(!(xCord&1)) {                                  //on two tiles along x-axis
    tile1_type = grid1->getTileColor(xCord/2, (zCord + 1)/2);
    tile2_type = grid1->getTileColor(xCord/2 + 1, (zCord + 1)/2);

    if( tile1_type == "NULL"  || tile2_type == "NULL" ) {
      block->freeFall();
    }
    else {
      tile1 = grid1->getTile(xCord/2, (zCord + 1)/2);
      tile2 = grid1->getTile(xCord/2 + 1, (zCord + 1)/2);
      tile1->press(0);
      tile2->press(0);
    }
  }

  else if(!(zCord&1)) {                                  //on two tiles along z-axis
    tile1_type = grid1->getTileColor((xCord + 1)/2, zCord/2);
    tile2_type = grid1->getTileColor((xCord + 1)/2, zCord/2 + 1);

    if( tile1_type == "NULL"  || tile2_type == "NULL" ) {
      block->freeFall();
    }
    else {
      tile1 = grid1->getTile((xCord + 1)/2, zCord/2);
      tile2 = grid1->getTile((xCord + 1)/2, zCord/2 + 1);
      tile1->press(0);
      tile2->press(0);
    }
  }
}

void displayObjects() {
  for(auto tilerow: *(tileCollection)) {
    for(auto tile :tilerow) {
      if(tile != NULL) {
        tile->draw();
      }
    }
  }
  block->draw();
  score->setVal(moves * 10);
  score->render();
}

void setupGridAndBlock(int level){
  grid1 = new grid(level);
  tileCollection = grid1->gettileCollection();
  grid1->getGridDimensions(&grid_length,&grid_breadth,&xoffset,&zoffset);
  grid_center_x = (float(grid_length/2) - xoffset) * scalingFactor;
  grid_center_z = (float(grid_breadth/2) - zoffset) * scalingFactor;
  block = new blocks(2, 0, 1,xoffset,zoffset);        //NOTE give co-ordinates of grid as (z,x)
  updateLevel = false;
}

int main()
{
  basicSetup setup=basicSetup(window_width,window_height);
  GLFWwindow* window = setup.initGLFW();

  setup.initGL(window);
  last_update_time = glfwGetTime();
  gameOver = false;
  moves = 0;
  level = 0;

  mpg123_handle *mh;
  unsigned char *buffer;
  size_t buffer_size;
  size_t done;
  int err;

  int driver;
  ao_device *dev;

  ao_sample_format format;
  int channels, encoding;
  long rate;

  /* initializations */
  ao_initialize();
  driver = ao_default_driver_id();
  mpg123_init();
  mh = mpg123_new(NULL, &err);
  buffer_size = 4096;
  buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

  /* open the file and get the decoding format */
  mpg123_open(mh, "godzilla.mp3");
  mpg123_getformat(mh, &rate, &channels, &encoding);

  /* set the output format and open the output device */
  format.bits = mpg123_encsize(encoding) * BITS;
  format.rate = rate;
  format.channels = channels;
  format.byte_format = AO_FMT_NATIVE;
  format.matrix = 0;
  dev = ao_open_live(driver, &format, NULL);


  score = new Text("nr/number.obj");

  brick1::initModel();
  brick2::initModel();
  switchbrick::initModel();
  fragile::initModel();
  goaltile::initModel();

  level = 0;
  setupGridAndBlock(level);

  cam = new camera(grid_center_x,grid_center_z,block);

  while(gameOver == false){

    if (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK) {
      ao_play(dev, (char *)buffer, done);
    }
    else {
      mpg123_seek(mh, 0, SEEK_SET); // loop audio from start again if ended
    }

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    current_time = glfwGetTime();
    if (((current_time - last_update_time) > delay_time) && updateLevel) {
      setupGridAndBlock(1);
      updateLevel = false;
    }

    if( block->getchangedCoordinates() ) {
      block->togglechangedCoordinates();              //NOTE order of toggling matters here...
      checkFall();
      moves ++ ;
      grid1->toggleupdated();
      cout << moves << endl;
    }
    else if( grid1->isupdated() ) {
      grid1->toggleupdated();
      checkFall();
    }

    if(fpv) {
      cam->setFirstPersonView(firstPersonAngle);
    }
    else if(heliView) {
      if(draggedRotate) {
        glfwGetCursorPos(window, &currentcursor_x, &currentcursor_y);
        heliRotationAngle = heliRotationAngle + (currentcursor_x - cursor_x);
        glfwGetCursorPos(window, &cursor_x, &cursor_y);
      }
      cam->setHeliView(grid_center_x,grid_center_z,heliRotationAngle,heliZoomFactor);
    }
    else if(followView) {
      cam->setFollowView();
    }

    displayObjects();

    glfwSwapBuffers(window);
    glfwPollEvents();
  };

  free(buffer);

  /* clean up */
  ao_close(dev);
  mpg123_close(mh);
  mpg123_delete(mh);
  mpg123_exit();
  ao_shutdown();

  cout << "Game Over" << endl << "Your Score:"  << endl;
  glfwTerminate();
  exit(0);
}
