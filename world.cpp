// Draw the portions of the world

#include "CSCIx229.h"
#include "cylinder.h"
#include "torus.h"
#include "cube.h"
#include "triangularPrism.h"
#include "cone.h"
#include "sphere.h"
#include "bicycle.h"
#include "skybox.h"
#include "physics.h"

#include "world.h"

#define nullptr 0

void drawSky(){
  glDisable(GL_DEPTH_TEST);
  glDepthMask(GL_FALSE);
  
  glPushMatrix();
  glPushAttrib(GL_TRANSFORM_BIT|GL_ENABLE_BIT);

  drawSkybox(50.0);

  glPopAttrib();
  glPopMatrix();

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
}

// Transform Bullet Coordinates to my OpenGL
float* getCoordinates(btTransform& transform, float* given = nullptr){
  float * coord = nullptr;
  if(given == nullptr){
    coord = new float[3];
  }else{
    coord = given;
  }
  
  coord[0]=getXFromBullet(transform);
  coord[1]=getYFromBullet(transform);
  coord[2]=getZFromBullet(transform);
  
  return coord;
}

void drawStaticWorld()
{
  float shinyvec[1] = {1};
  float* coord = new float[3];
  glPushMatrix();
  
  glRotatef(-90, 1,0,0);

  // floor
  glColor3f(0,0,1);
  cube(0,0,-1, 50,50,1, 0, shinyvec);

  // Scene Objects
  glColor3f(1,0,1);

  // Bridge structure
  getCoordinates(cylinders[0]->getWorldTransform(), coord);
  cylinder(coord[0],coord[1],coord[2]-1, 0.5, 2, 0,0,0, 1,1,1);
  getCoordinates(cylinders[1]->getWorldTransform(), coord);
  cylinder(coord[0],coord[1],coord[2]-1, 0.5, 2, 0,0,0, 1,1,1);
  cube(2,1,1, 1,3,0.2, 0, shinyvec);
  triangularPrism(2,-2.5,0, 0,0,0, 1,1,1.2, shinyvec);
  triangularPrism(2,4.5,0, 0,0,180, 1,1,1.2, shinyvec);

  glColor3f(1,0,1);
  
  // A bicycle
  getCoordinates(bicycles[0]->getWorldTransform(), coord);
  bicycle(coord[0],coord[1],coord[2], 90,90,0, 0.5,0.5,0.5);
  getCoordinates(bicycles[1]->getWorldTransform(), coord);
  bicycle(coord[0],coord[1],coord[2], 90,0,0, 0.5,0.5,0.5);

  // Boundary boxes
  getCoordinates(boxes[0]->getWorldTransform(), coord);
  cube(coord[0],coord[1],coord[2], 21,0.5,1, 0,shinyvec);
  getCoordinates(boxes[1]->getWorldTransform(), coord);
  cube(coord[0],coord[1],coord[2], 21,0.5,1, 0,shinyvec);
  getCoordinates(boxes[2]->getWorldTransform(), coord);
  cube(coord[0],coord[1],coord[2], 0.5,21,1, 0,shinyvec);
  getCoordinates(boxes[3]->getWorldTransform(), coord);
  cube(coord[0],coord[1],coord[2], 0.5,21,1, 0,shinyvec);

  glColor3f(1,0,1);
  
  // Spheres
  getCoordinates(spheres[0]->getWorldTransform(), coord);
  sphere(coord[0],coord[1],coord[2], 1, shinyvec, 0);
  getCoordinates(spheres[1]->getWorldTransform(), coord);
  sphere(coord[0],coord[1],coord[2], 1, shinyvec, 0);
  getCoordinates(spheres[2]->getWorldTransform(), coord);
  sphere(coord[0],coord[1],coord[2], 1, shinyvec, 0);
  getCoordinates(spheres[3]->getWorldTransform(), coord);
  sphere(coord[0],coord[1],coord[2], 1, shinyvec, 0);
  getCoordinates(spheres[4]->getWorldTransform(), coord);
  sphere(coord[0],coord[1],coord[2], 2, shinyvec, 0);
  getCoordinates(spheres[5]->getWorldTransform(), coord);
  sphere(coord[0],coord[1],coord[2], 2, shinyvec, 0);
  getCoordinates(spheres[6]->getWorldTransform(), coord);
  sphere(coord[0],coord[1],coord[2], 2, shinyvec, 0);
  getCoordinates(spheres[7]->getWorldTransform(), coord);
  sphere(coord[0],coord[1],coord[2], 2, shinyvec, 0);

  glColor3f(1,0,1);
  
  // Cones
  getCoordinates(cones[0]->getWorldTransform(), coord);
  cone(coord[0],coord[1],coord[2]-1, 0,0,0, 1,1,1);
  getCoordinates(cones[1]->getWorldTransform(), coord);
  cone(coord[0],coord[1],coord[2]-1, 0,0,0, 1,1,1);
  getCoordinates(cones[2]->getWorldTransform(), coord);
  cone(coord[0],coord[1],coord[2]-1, 0,0,0, 1,1,1);
  getCoordinates(cones[3]->getWorldTransform(), coord);
  cone(coord[0],coord[1],coord[2]-1, 0,0,0, 1,1,1);
  getCoordinates(cones[4]->getWorldTransform(), coord);
  cone(coord[0],coord[1],coord[2]-1, 0,0,0, 1,1,2);
  getCoordinates(cones[5]->getWorldTransform(), coord);
  cone(coord[0],coord[1],coord[2]-1, 0,0,0, 1,1,2);
  getCoordinates(cones[6]->getWorldTransform(), coord);
  cone(coord[0],coord[1],coord[2]-1, 0,0,0, 1,1,1);
  getCoordinates(cones[7]->getWorldTransform(), coord);
  cone(coord[0],coord[1],coord[2]-1, 0,0,0, 1,1,1);

  glColor3f(1,0,1);
  
  // Triangular Prisms
  getCoordinates(triangularPrisms[0]->getWorldTransform(), coord);
  triangularPrism(coord[0],coord[1],coord[2], -90,180,0, 1,1,1, shinyvec);
  getCoordinates(triangularPrisms[1]->getWorldTransform(), coord);
  triangularPrism(coord[0],coord[1],coord[2], -90,180,0, 1,1,1, shinyvec);
  getCoordinates(triangularPrisms[2]->getWorldTransform(), coord);
  triangularPrism(coord[0],coord[1],coord[2], -90,180,0, 1,1,1, shinyvec);
  getCoordinates(triangularPrisms[3]->getWorldTransform(), coord);
  triangularPrism(coord[0],coord[1],coord[2], -90,180,0, 1,1,1, shinyvec);
  
  glColor3f(1,1,1);
  glPopMatrix();
}

void drawDynamicWorld()
{
  glPushMatrix();
  glRotatef(-90, 1,0,0);

  drawCharacter();
  
  glPopMatrix();
}

void drawCharacter()
{
  const float shinyvec[1] = {1};
  glPushMatrix();
  btTransform characterTransform = worldCharacter->getWorldTransform();
  float* coord = getCoordinates(characterTransform);
  cube(coord[0],coord[1],coord[2], 0.2,0.2,0.2, 0, shinyvec);
  delete[] coord;
  glPopMatrix();
}
