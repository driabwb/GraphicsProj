// Draw the portions of the world

#include "CSCIx229.h"
#include "cylinder.h"
#include "torus.h"
#include "cube.h"
#include "triangularPrism.h"
#include "cone.h"

#include "world.h"

void drawStaticWorld()
{
  float shinyvec[1] = {1};
  glPushMatrix();
  
  glRotatef(-90, 1,0,0);

  cylinder(2,0,0, 0.5, 2, 0,0,0, 1,1,1);
  cylinder(2,2,0, 0.5, 2, 0,0,0, 1,1,1);
  cube(2,1,1, 1,3,0.2, 0, shinyvec);
  triangularPrism(2,-2.5,0, 0,0,0, 1,1,1.2, shinyvec);
  triangularPrism(2,4.5,0, 0,0,180, 1,1,1.2, shinyvec);
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

  cube(0,0,0, 0.1,0.1,0.1, 0, shinyvec);
  
  glPopMatrix();
}
