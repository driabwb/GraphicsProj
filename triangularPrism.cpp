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
		     double rx, double ry, double rz,
		     double dx, double dy, double dz,
		     float* shinyvec)
{
  // Save Transform
  glPushMatrix();
  // Offset
  glTranslated(x,y,z);
  glRotatef(rx, 1,0,0);
  glRotatef(ry, 0,1,0);
  glRotatef(rz, 0,0,1);
  glScaled(dx,dy,dz);

  //End Triangles
  glBegin(GL_TRIANGLES);
  glNormal3d(1,0,0);
  glVertex3f(1,-1,0);
  glVertex3f(1,1,0);
  glVertex3f(1,0.5,1);
  glEnd();
  glBegin(GL_TRIANGLES);
  glNormal3d(-1,0,0);
  glVertex3f(-1,0.5,1);
  glVertex3f(-1,1,0);
  glVertex3f(-1,-1,0);
  glEnd();

  // Sides
  glBegin(GL_QUADS);
  // Side 1
  glNormal3d(0,2,1);
  glVertex3f(1,1,0);
  glVertex3f(-1,1,0);
  glVertex3f(-1,0.5,1);
  glVertex3f(1,0.5,1);
  // Side 2
  glNormal3d(0,-2,3);
  glVertex3f(-1,0.5,1);
  glVertex3f(-1,-1,0);
  glVertex3f(1,-1,0);
  glVertex3f(1,0.5,1);
  // Side 3
  glNormal3d(0,0,-4);
  glVertex3f(1,1,0);
  glVertex3f(1,-1,0);
  glVertex3f(-1,-1,0);
  glVertex3f(-1,1,0);
  glEnd();

  // Undo transformations
  glPopMatrix();
}
