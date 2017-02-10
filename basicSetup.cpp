#include "camera.h"
#include "basicSetup.h"
#include "loadShaders.h"
#include "reshapeWindow.h"

basicSetup::basicSetup(int intialWidth, int intialHeight){
  width = intialWidth;
  height = intialHeight;
}


void basicSetup::quit(GLFWwindow * window){
  glfwDestroyWindow(window);
  glfwTerminate();
}

void basicSetup::setWidth (int newWidth){
  width = newWidth;
}
void basicSetup::setHeight (int newHeight){
  height = newHeight;
}

GLFWwindow* basicSetup::initGLFW ()
{
  GLFWwindow* window; // window desciptor/handle

  if (!glfwInit()) {
    //        exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //window not resizable by user
  window = glfwCreateWindow(width, height, "Vaibhav Gupta(201502166)", NULL, NULL);

  if (!window) {
    glfwTerminate();
    //        exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  glfwSwapInterval( 1 );
  srand (time(NULL));
  /*************Registering callbacks to handle various events***************/
  glfwSetFramebufferSizeCallback(window, reshapeWindow::reshapeWindowFunction);
  glfwSetWindowSizeCallback(window, reshapeWindow::reshapeWindowFunction);
  glfwSetWindowCloseCallback(window, basicSetup::quit);
  glfwSetKeyCallback(window, keyboard);      // general keyboard input
  glfwSetMouseButtonCallback(window, mouseButton);  // mouse button clicks
  glfwSetScrollCallback(window, scroll_callback);
  return window;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void basicSetup::initGL (GLFWwindow* window)
{
  //loading and linking shaders
  GLuint VertexShaderID = loadShaders::processShaderData( "Sample_GL.vert" , GL_VERTEX_SHADER );
  GLuint FragmentShaderID = loadShaders::processShaderData( "Sample_GL.frag" , GL_FRAGMENT_SHADER );
  GLuint programID = loadShaders::linkProgram(VertexShaderID , FragmentShaderID);
  glUseProgram (programID);

  // Get a handle for our "MVP" uniform
  GLMatrices::Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

  reshapeWindow::reshapeWindowFunction(window, width, height);
  camera::setCameraPosition();
  glClearColor (0, 0, 1, 1); // R, G, B, A
  glClearDepth (1.0f);
  glEnable (GL_DEPTH_TEST);
  glDepthFunc (GL_LEQUAL);
}
