// Draw Triangular Prisms

#include "CSCIx229.h"
#include "triangularPrism.h"

/*
 * Draw a triangular prism
 *     at (x,y,z)
 *     scaled to (dx,dy,dz)
 *
 */

void triangularPrism(double x, double y, double z,
			    double dx, double dy, double dz,
			    float* shinyvec)
{
  // Save Transform
  glPushMatrix();
  // Offset
  glTranslated(x,y,z);
  glScaled(dx,dy,dz);

  //End Triangles
  glBegin(GL_TRIANGLES);
  glColor3f(1,0,0);
  glNormal3d(1,0,0);
  glVertex3f(1,-1,0);
  glVertex3f(1,1,0);
  glVertex3f(1,0.5,1);
  glEnd();
  glBegin(GL_TRIANGLES);
  glNormal3d(-1,0,0);
  glColor3f(0,1,0);
  glVertex3f(-1,0.5,1);
  glVertex3f(-1,1,0);
  glVertex3f(-1,-1,0);
  glEnd();

  // Sides
  glBegin(GL_QUADS);
  // Side 1
  glNormal3d(0,2,1);
  glColor3f(0,0,1);
  glVertex3f(1,1,0);
  glVertex3f(-1,1,0);
  glVertex3f(-1,0.5,1);
  glVertex3f(1,0.5,1);
  // Side 2
  glNormal3d(0,-2,3);
  glColor3f(0,1,0);
  glVertex3f(-1,0.5,1);
  glVertex3f(-1,-1,0);
  glVertex3f(1,-1,0);
  glVertex3f(1,0.5,1);
  // Side 3
  glNormal3d(0,0,-4);
  glColor3f(1,0,0);
  glVertex3f(1,1,0);
  glVertex3f(1,-1,0);
  glVertex3f(-1,-1,0);
  glVertex3f(-1,1,0);
  glEnd();

  // Undo transformations
  glPopMatrix();
}
