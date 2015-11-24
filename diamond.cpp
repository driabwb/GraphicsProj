// Draw a diamond

#include "CSCIx229.h"
#include "diamond.h"

void diamond(double x, double y, double z,
	     double rx, double ry, double rz,
	     double sx, double sy, double sz)
{
  glPushMatrix();

  glTranslated(x,y,z);
  glRotated(rx, 1,0,0);
  glRotated(ry, 0,1,0);
  glRotated(rz, 0,0,1);
  glScaled(sx,sy,sz);

  glBegin(GL_TRIANGLES);

  glNormal3f(1,1,1);
  glVertex3f(0.0,0.0,1.0);
  glVertex3f(1.0,0.0,0.0);
  glVertex3f(0.0,1.0,0.0);

  glNormal3f(-1,1,1);
  glVertex3f(0.0,0.0,1.0);
  glVertex3f(0.0,1.0,0.0);
  glVertex3f(-1.0,0.0,0.0);

  glNormal3f(-1,-1,1);
  glVertex3f(0.0,0.0,1.0);
  glVertex3f(-1.0,0.0,0.0);
  glVertex3f(0.0,-1.0,0.0);

  glNormal3f(1,-1,1);
  glVertex3f(0.0,0.0,1.0);
  glVertex3f(0.0,-1.0,0.0);
  glVertex3f(1.0,0.0,0.0);
  
  glEnd();

  glBegin(GL_TRIANGLES);

  glNormal3f(1,1,-1);
  glVertex3f(0.0,0.0,-1.0);
  glVertex3f(0.0,1.0,0.0);
  glVertex3f(1.0,0.0,0.0);

  glNormal3f(-1,1,-1);
  glVertex3f(0.0,0.0,-1.0);
  glVertex3f(-1.0,0.0,0.0);
  glVertex3f(0.0,1.0,0.0);

  glNormal3f(-1,-1,-1);
  glVertex3f(0.0,0.0,-1.0);
  glVertex3f(0.0,-1.0,0.0);
  glVertex3f(-1.0,0.0,0.0);

  glNormal3f(1,-1,-1);
  glVertex3f(0.0,0.0,-1.0);
  glVertex3f(1.0,0.0,0.0);
  glVertex3f(0.0,-1.0,0.0);
  
  glEnd();
  
  glPopMatrix();
}
