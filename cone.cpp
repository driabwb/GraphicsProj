// draw a cone

#include "CSCIx229.h"
#include "cone.h"

void cone(double x, double y, double z,
	  double rx, double ry, double rz,
	  double sx, double sy, double sz)
{
  int th;
  const int inc = 10;

  glPushMatrix();

  glTranslated(x,y,z);
  glRotated(rx, 1,0,0);
  glRotated(ry, 0,1,0);
  glRotated(rz, 0,0,1);
  glScaled(sx,sy,sz);

  // Bottom
  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0,0,1);
  glVertex3f(0,0,0);
  for(th=0; th<360; th+=inc){
    glVertex3f(Cos(th+inc),Sin(th+inc),0);
    glVertex3f(Cos(th),Sin(th),0);
  }
  glEnd();

  glBegin(GL_TRIANGLES);
  for(th=0; th < 360; th++){
    glNormal3f(Cos(th+inc/2),Sin(th+inc/2), 1);
    glVertex3f(0,0,1);
    glNormal3f(Cos(th),Sin(th),1);
    glVertex3f(Cos(th),Sin(th),0);
    glNormal3f(Cos(th+inc),Sin(th+inc),1);
    glVertex3f(Cos(th+inc),Sin(th+inc),0);
  }
  glEnd();
  glPopMatrix();
}
