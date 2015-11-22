#ifndef _BICYCLE_H_
#define _BICYCLE_H_

void wheel(double x, double y, double z,
	   double rx, double ry, double rz,
	   double sx, double sy, double sz,
	   double r);
void pedal(double x, double y, double z, double len);
void halfHandleBar(double x, double y, double z,
		   double rx, double ry, double rz,
		   double sx, double sy, double sz);
void frontFork(double x, double y, double z,
	       double rx, double ry, double rz,
	       double sx, double sy, double sz,
	       double wh, double w, double h);
void frontPiece(double x, double y, double z,
		double rx, double ry, double rz,
		double sx, double sy, double sz);
void body(double x, double y, double z,
	  double rx, double ry, double rz,
	  double sx, double sy, double sz);
void bicycle(double x, double y, double z,
	     double rx, double ry, double rz,
	     double sx, double sy, double sz);

#endif
