// Draw a torus

#include "CSCIx229.h"
#include "torus.h"


static void Vertex(int ph, int th, double c, double a)
{
  double x = (c + a*Cos(ph))*Cos(th);
  double y = (c + a*Cos(ph))*Sin(th);
  double z = a*Sin(ph);
  double nx = a*Cos(ph)*Cos(th)*(c+a*Cos(ph));
  double ny = a*Cos(ph)*Sin(th)*(c+a*Cos(ph));
  double nz = a*Sin(ph)*(c+a*Cos(ph));
  glNormal3d(nx,ny,nz);
  glVertex3d(x,y,z);
}


/*
 * Draw a torus centered at (x,y,z)
 *     with a radius to center of the ring c
 *     with a radius of the right a
 *     and rotated (dx,dy,dz)
 *     and scaled  (sx,sy,sz)
 *     and in n sides
 */

void torus(double x, double y, double z,
	   double c, double a,
	   double dx, double dy, double dz,
	   double sx, double sy, double sz,
	   int n)
{
  int inc = 360/n;
  int ph, th;

  // Save transform
  glPushMatrix();
  // Local transforms
  glTranslated(x,y,z);
  glRotated(dx,1,0,0);
  glRotated(dy,0,1,0);
  glRotated(dz,0,0,1);
  glScaled(sx,sy,sz);

  for(ph=0; ph<=360; ph+=inc){
    glBegin(GL_QUAD_STRIP);
    for(th=0; th<=360; th+=inc){
      Vertex(th, ph, c, a);
      Vertex(th, ph+inc, c, a);
    }
    glEnd();
  }

  glPopMatrix();
}

void partialTorus(double x, double y, double z,
		  double c, double a,
		  double dx, double dy, double dz,
		  double sx, double sy, double sz,
		  int n, int portion)
{
  int inc = 360/n;
  int ph, th;

  // Save transform
  glPushMatrix();
  // Local transforms
  glTranslated(x,y,z);
  glRotated(dx,1,0,0);
  glRotated(dy,0,1,0);
  glRotated(dz,0,0,1);
  glScaled(sx,sy,sz);

  for(ph=0; ph<=portion; ph+=inc){
    glBegin(GL_QUAD_STRIP);
    for(th=0; th<=360; th+=inc){
      Vertex(th, ph, c, a);
      Vertex(th, ph+inc, c, a);
    }
    glEnd();
  }
  glPushMatrix();
  glTranslated(c,0,0);
  glScaled(a,1,a);
  glBegin(GL_TRIANGLE_FAN);
  glVertex3d(0,0,0);
  for(th=0; th<=360; th+=inc){
    glVertex3d(Cos(th),0,Sin(th));
  }
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glRotated(portion, 0,0,1);
  glTranslated(c,0,0);
  glScaled(a,1,a);
  glBegin(GL_TRIANGLE_FAN);
  glVertex3d(0,0,0);
  for(th=360; th>=0; th-=inc){
    glVertex3d(Cos(th),0,Sin(th));
  }
  glEnd();
  glPopMatrix();
  glPopMatrix();
}
