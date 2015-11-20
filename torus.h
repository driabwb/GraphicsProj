#ifndef _TORUS_H_
#define _TORUS_H_

void torus(double x, double y, double z,
	   double c, double a,
	   double dx, double dy, double dz,
	   double sx, double sy, double sz,
	   int n);

void partialTorus(double x, double y, double z,
		  double c, double a,
		  double dx, double dy, double dz,
		  double sx, double sy, double sz,
		  int n, int portion);

#endif
