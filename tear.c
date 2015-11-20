// Draw Teardrops

#include "CSCIx229.h"
#include "tear.h"

/*
 *  Draw vertex in polar coordinates
 */
static void tearVertex(double th,double ph)
{
  glColor3f(1,0,0);
  //glColor3f(Cos(th)*Cos(th) , Sin(ph)*Sin(ph) , Sin(th)*Sin(th));
  glVertex3d(Cos(th) ,
	     Sin(th)*pow(Sin(th/2),4.0)*Sin(ph) ,
	     Sin(th)*pow(Sin(th/2),4.0)*Cos(ph));
}

static void tearNormal(double th, double ph)
{
  glNormal3d(1*pow(Sin(th/2),9)*(7*Cos(th/2)+3*Cos(3*th/2)),
	     1*pow(Sin(th/2),4)*pow(Sin(th),2)*Sin(ph),
	     1*Cos(ph)*pow(Sin(th/2),4)*pow(Sin(th),2));
}

/*
 *  Draw a tear drop 
 *     at (x,y,z)
 *     radius (r)
 *     rotated (rx, ry, rz)
 */
void tear(double x,double y,double z,double r,
	  double rx, double ry, double rz,
	  float* shinyvec)
{
   const int d=20;
   int th,ph;
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   
   glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   
   
   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);

   /* Unimplemented feature, create transformation based upon rx,ry,rz not compound transform */
   glRotated(rx, 1,0,0);
   glRotated(ry, 0,Cos(rx),Sin(rx));
   glRotated(rz, Sin(ry),Sin(rx),Cos(rx)*Cos(ry));
   
   glScaled(r,r,r);

   //  Top
   glBegin(GL_TRIANGLE_FAN);
   tearNormal(0,0);
   tearVertex(0,0);
   for (th=0;th<180;th+=d)
   {
     tearNormal(d,th);
     tearVertex(d,th);
   }
   glEnd();
   
   //  Latitude bands
   for (ph=d;ph<=360;ph+=d)
   {
     glBegin(GL_QUAD_STRIP);
     for (th=0;th<=360;th+=d)
     {
       tearNormal(th,ph);
       tearVertex(th,ph);
       tearNormal(th,ph+d);
       tearVertex(th,ph+d);
	 }
      glEnd();
   }

   //  Bottom
   glBegin(GL_TRIANGLE_FAN);
   tearNormal(360,360);
   tearVertex(360,360);
   for (th=0;th<360;th+=d)
   {
     tearNormal(360-d,th);
     tearVertex(360-d,th);
   }
   glEnd();

   //  Undo transformations
   glPopMatrix();
}

