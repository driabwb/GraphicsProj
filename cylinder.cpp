// Draw cylinders

#include "CSCIx229.h"
#include "cylinder.h"

void cylinder(double x, double y, double z,
	      double r, double h,
	      double rx, double ry, double rz,
	      double sx, double sy, double sz)
{
  int inc = 20;
  int th;
  double height, height2;
  double hinc = 4.0;
  
  glPushMatrix();

  glTranslated(x,y,z);
  glRotated(rx,1,0,0);
  glRotated(ry,0,1,0);
  glRotated(rx,0,0,1);
  glScaled(sx,sy,sz*h);

  
  for(height = 0.0; height < 1; height = height2){
    height2 = height + hinc;
    if(height2 > 1)
      height2 = 1;
    
    glBegin(GL_QUAD_STRIP);
    for(th=0; th<=360; th+=inc){
      glNormal3d(r*Cos(th), r*Sin(th), 0);
      glVertex3d(r*Cos(th), r*Sin(th), height2);
      glVertex3d(r*Cos(th), r*Sin(th), height);
    }
    glEnd();
  }

  glBegin(GL_TRIANGLE_FAN);
  glNormal3d(0,0,-1);
  glVertex3d(0,0,0);
  for(th=360;th>=0;th-=inc){
    glVertex3d(r*Cos(th), r*Sin(th), 0);
  }
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
  glNormal3d(0,0,1);	
  glVertex3d(0,0,1);
  for(th=0;th<=360;th+=inc){
    glVertex3d(r*Cos(th), r*Sin(th), 1);
  }
  glEnd();

  glPopMatrix();
}
