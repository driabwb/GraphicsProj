// Draw a tetrahedron

#include "CSCIx229.h"
#include "tetrahedron.h"

static void setNormal(double x0, double y0, double z0,
		      double x1, double y1, double z1,
		      double x2, double y2, double z2)
{
  double wx=x1-x0;
  double wy=y1-y0;
  double wz=z1-z0;
  double vx=x2-x0;
  double vy=y2-y0;
  double vz=z2-z0;
  glNormal3f(vy*wz-vz*wy, vz*wx-vx*wz, vx*wy-vy*wx);
}

void tetrahedron(double x0, double y0, double z0,
		 double x1, double y1, double z1,
		 double x2, double y2, double z2,
		 double x3, double y3, double z3)
{
  glPushMatrix();

  //Face 1, pts 0,1,2
  glBegin(GL_TRIANGLES);
  glColor3f(1,0,0);
  setNormal(x0,y0,z0, x1,y1,z1, x2,y2,z2);
  glVertex3f(x0,y0,z0);
  glVertex3f(x2,y2,z2);
  glVertex3f(x1,y1,z1);
  glEnd();
  //Face 2, pts 0,2,3
  glBegin(GL_TRIANGLES);
  glColor3f(0,1,0);
  setNormal(x0,y0,z0, x2,y2,z2, x3,y3,z3);
  glVertex3f(x0,y0,z0);
  glVertex3f(x3,y3,z3);
  glVertex3f(x2,y2,z2);
  glEnd();
  //Face 3, pts 0,3,1
  glBegin(GL_TRIANGLES);
  glColor3f(0,0,1);
  setNormal(x0,y0,z0, x3,y3,z3, x1,y1,z1);
  glVertex3f(x0,y0,z0);
  glVertex3f(x1,y1,z1);
  glVertex3f(x3,y3,z3);
  glEnd();
  //Face 4, pts 1,2,3
  glBegin(GL_TRIANGLES);
  glColor3f(1,1,0);
  setNormal(x1,y1,z1, x3,y3,z3, x2,y2,z2);
  glVertex3f(x1,y1,z1);
  glVertex3f(x2,y2,z2);
  glVertex3f(x3,y3,z3);
  glEnd();
  
  glPopMatrix();
}
