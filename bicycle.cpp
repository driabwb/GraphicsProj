// Draw a bicycle

#include "CSCIx229.h"
#include "bicycle.h"
#include "torus.h"
#include "cube.h"
#include "cylinder.h"

void wheel(double x, double y, double z,
	   double rx, double ry, double rz,
	   double sx, double sy, double sz,
	   double r)
{
  const int inc = 18;
  int th;
  glPushMatrix();

  glTranslated(x,y,z);
  glRotated(rx, 1,0,0);
  glRotated(ry, 0,1,0);
  glRotated(rz, 0,0,1);
  glRotated(90, 0,1,0);
  glScaled(sx,sy,sz);
  // Outer ring
  torus(0,0,0, r,0.125, 0,0,0, 1,1,1, 60);
  // Wheel center
  cylinder(0,0,-0.05, 0.1*r,0.25, 0,0,0, 1,1,1);
  cylinder(0,0,0.05, 0.1*r,0.25, 0,180,0, 1,1,1);
  // Spokes
  for(th=0; th<=360; th+=inc){
    cylinder(0,0,0, 0.05,r, 90,th,0, 1,1,1);
  }
  // Center bar to connect to forks
  cylinder(0,0,0, 0.02*r,0.3, 0,0,0, 1,1,1);
  cylinder(0,0,0, 0.02*r,0.3, 0,180,0, 1,1,1);  
  
  glPopMatrix();
  
}

void pedal(double x, double y, double z, double rot)
{
  float shinyvec[] = {1};
  glPushMatrix();

  glTranslated(x,y,z);
  glRotated(rot, 0,0,1);

  cylinder(0,0,0, 0.19,0.5, 0,0,0, 1,1,1);
  cube(0,0,0.5, 0.2,1,0.2, 0, shinyvec);
  cube(0,0,1.3, 0.2,0.2,1, 0, shinyvec);
  cube(0,1,1.3, 0.2,0.2,1, 0, shinyvec);
  cube(0,-1,1.3, 0.2,0.2,1, 0, shinyvec);
  cube(0,0,2.1, 0.2,1,0.2, 0, shinyvec);
  
  glPopMatrix();
  
}

void halfHandleBar(double x, double y, double z,
		   double rx, double ry, double rz,
		   double sx, double sy, double sz)
{

  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(rx, 1,0,0);
  glRotated(ry, 0,1,0);
  glRotated(rz, 0,0,1);
  glScaled(sx,sy,sz);

  cylinder(0,0,0, 1,2, 0,90,0, 1,1,1);
  partialTorus(4.25,0,0, 3,0.5, 0,0,0, 1,1,1, 20, 175);
  cylinder(6.5,0,0, 1,3, 0,90,0, 1,1,1);
  cylinder(7.5,0,0, 2,0.1, 0,90,0, 1,1,1);
  
  glPopMatrix();
  
}

void frontFork(double x, double y, double z,
	       double rx, double ry, double rz,
	       double sx, double sy, double sz,
	       double wh, double w, double h)
{
  glPushMatrix();

  glTranslated(x,y,z);
  glRotated(rx, 1,0,0);
  glRotated(ry, 0,1,0);
  glRotated(rz, 0,0,1);
  glScaled(sx,sy,sz);

  cylinder(w,0,-0.05, 0.5,wh+0.05, 0,0,0, 1,1,1);
  cylinder(-w,0,-0.05, 0.5,wh+0.05, 0,0,0, 1,1,1);
  partialTorus(0,0,wh, w,0.5, 90,0,0, 1,1,1, 20, 175);
  cylinder(0,0,wh+w, 0.5,h, 0,0,0, 1,1,1);

  glPopMatrix();
}

void frontPiece(double x, double y, double z,
		double rx, double ry, double rz,
		double sx, double sy, double sz)
{
  glPushMatrix();

  const double wh = 3;
  const double w = 1;
  const double h = 2;
  
  glTranslated(x,y,z);
  glRotated(rx, 1,0,0);
  glRotated(ry, 0,1,0);
  glRotated(rz, 0,0,1);
  glScaled(sx,sy,sz);

  wheel(0,0,0, 0,0,0, 1,1,1, wh);
  frontFork(0,0,0, 0,0,0, 0.3,0.3,1, wh, w, h);
  halfHandleBar(0,0,wh+w+h, 0,0,0, 0.2,0.2,0.2);
  halfHandleBar(0,0,wh+w+h, 180,0,180, 0.2,0.2,0.2);

  glPopMatrix();
}

void body(double x, double y, double z,
	  double rx, double ry, double rz,
	  double sx, double sy, double sz)

{
  const double r=0.2;  // radius of the tubes
  const double r1=3.5; // radius of the first torus
  const double r2=1;   // radius of the second torus
  const double wr=1;   // radius of the wheel
  const double w=1;    // width the fork is spread over
  const double h=1.7;  // length of the bar above the fork
  const double theta=80;            // angle the first torus goes through
  const double phi=10;              // angle the second torus goes through
  const double alpha=270-theta+phi; // angle for finding torus/fork intersection
  const double beta=theta-phi;      // angle the fork goes off at
  const double torusx=(r1+r2)*Cos(90-theta); // the center of the second torus x
  const double torusy=(r1+r2)*Sin(90-theta); // the center of the second torus y
  const double wheelx=(wr+w+h)*Cos(-1*beta)+r2*Cos(alpha)+torusx; // the center of the wheel x
  const double wheely=(wr+w+h)*Sin(-1*beta)+r2*Sin(alpha)+torusy; // the center of the wheel y


  glPushMatrix();

  glTranslated(x,y,z);
  glRotated(rx, 1,0,0);
  glRotated(ry, 0,1,0);
  glRotated(rz, 0,0,1);
  glScaled(sx,sy,sz);
  partialTorus(0,0,0, r1,r, 0,0,90-theta, 1,1,1, 360, theta);
  partialTorus(torusx,torusy,0, r2,r, 0,0,alpha-phi, 1,1,1, 360, phi);

  glPushMatrix();
  glTranslated(wheelx,wheely,0);  
  glRotated(-1*(beta), 0,0,1);
  frontFork(0,0,0, 0,-90,0, r/0.5,r/0.5,1, wr,w,h);
  glPopMatrix();

  wheel(wheelx,wheely,0, 0,90,0, 1,1,1, wr);
  
  glPopMatrix();
}

void bicycle(double x, double y, double z,
	     double rx, double ry, double rz,
	     double sx, double sy, double sz)
{
  glPushMatrix();

  glTranslated(x,y,z);
  glRotated(rx, 1,0,0);
  glRotated(ry, 0,1,0);
  glRotated(rz, 0,0,1);
  glScaled(sx,sy,sz);

  body(0.1,1,0, 0,0,0, 1,1,1);
  frontPiece(0,0,0, -90,0,90, 1,1,1);
  
  
  glPopMatrix();
}
