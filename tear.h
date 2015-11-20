#ifndef _TEAR_H_
#define _TEAR_H_

/*
 *  Draw a tear drop 
 *     at (x,y,z)
 *     radius (r)
 *     rotated (rx, ry, rz)
 */
void tear(double x,double y,double z,double r,
	  double rx, double ry, double rz,
	  float* shinyvec);

#endif
