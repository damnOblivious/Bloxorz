#include "camera.h"
#include "blocks.h"

camera::camera(float x,float z, blocks * Block) {
  myBlock = Block;
  setNormalView(x,z);
}

void camera::setTopView(float x,float z) {
  eye = glm::vec3(x, 7, z);
  target = glm::vec3(x,0,z);
  up = glm::vec3(0,0,-1);
  setViewMatrix();
}

void camera::setNormalView(float x,float z) {
  eye = glm::vec3(-3,3,3);
  target = glm::vec3(x,0,z);
  up = glm::vec3(0,1,0);
  setViewMatrix();
}

void camera::setHeliView(float x, float z, float rotationAngle, float zoomFactor) {
  eye = glm::vec3(zoomFactor * sin(glm::radians(rotationAngle)),zoomFactor,-1.0f * zoomFactor * cos(glm::radians(rotationAngle)));
  target = glm::vec3(x,0,z);
  up = glm::vec3(0,1,0);
  setViewMatrix();
}

void camera::setFollowView() {
  blockDimensions = myBlock->getBlockDimensions();        //width , height , breadth
  blockCenter = myBlock->getCenterPosition();             // x ,  y , z
  eye = glm::vec3(blockCenter.x , blockCenter.y + 4.0f, blockCenter.z- 3.0f);
  target = blockCenter;
  up = glm::vec3(0,1,0);
  setViewMatrix();
}

void camera::setFirstPersonView(int angle) {
  blockDimensions = myBlock->getBlockDimensions();        //width , height , breadth
  blockCenter = myBlock->getCenterPosition();             // x ,  y , z
  // cout << x << " " << z << " " << rotationAngle << " " << zoomFactor << endl;
  glm::vec3 topRightEye = glm::vec3(blockCenter.x + (blockDimensions.x)/2.0f, blockCenter.y + (blockDimensions.y)/2.0f, blockCenter.z);
  glm::vec3 topRightTarget = glm::vec3(blockCenter.x + (blockDimensions.x)*2.0f, blockCenter.y, blockCenter.z);

  glm::vec3 topLeftEye = glm::vec3(blockCenter.x - (blockDimensions.x)/2.0f, blockCenter.y + (blockDimensions.y)/2.0f, blockCenter.z);
  glm::vec3 topLeftTarget = glm::vec3(blockCenter.x - (blockDimensions.x)*2.0f, blockCenter.y, blockCenter.z);

  glm::vec3 topFrontEye = glm::vec3(blockCenter.x, blockCenter.y + (blockDimensions.y)/2.0f, blockCenter.z + (blockDimensions.z)/2.0f);
  glm::vec3 topFrontTarget = glm::vec3(blockCenter.x, blockCenter.y, blockCenter.z + (blockDimensions.z)*2.0f);

  glm::vec3 topBehindEye = glm::vec3(blockCenter.x, blockCenter.y + (blockDimensions.y)/2.0f, blockCenter.z - (blockDimensions.z)/2.0f);
  glm::vec3 topBehindTarget = glm::vec3(blockCenter.x, blockCenter.y, blockCenter.z - (blockDimensions.z)*2.0f);

  if((angle + 360) % 360 == 0){       //along +x front
    std::cout << "front" << std::endl;
    eye = topFrontEye;
    target = topFrontTarget;
  }
  if((angle + 360) % 360 == 90){        //along -z right
    std::cout << "1front" << std::endl;
    eye = topRightEye;
    target = topRightTarget;
  }
  if((angle + 360) % 360 == 180){       //along -x
    std::cout << "2front2" << std::endl;
    eye = topBehindEye;
    target = topBehindTarget;
  }
  if((angle + 360) % 360 == 270) {      //along +z
    std::cout << "3front3" << std::endl;
    eye = topLeftEye;
    target = topLeftTarget;
  }
  up = glm::vec3(0,1,0);
  setViewMatrix();
}

void camera::setViewMatrix() {
  GLMatrices::Matrices.view = glm::lookAt( eye, target, up );
}
