/*
 *  Final Project
 *  
 */
#include "CSCIx229.h"

// Shapes
#include "cube.h"
#include "sphere.h"
#include "triangularPrism.h"
#include "tear.h"
#include "torus.h"
#include "cylinder.h"
#include "bicycle.h"
#include "diamond.h"
#include "tetrahedron.h"
#include "cone.h"
#include "skybox.h"
#include "world.h"

#include "physics.h"

const int FIRST_PERSON = 2;
int fpth = 0;

int axes=1;       //  Display axes
int mode=2;       //  Projection mode
int move=1;       //  Move light
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int light=1;      //  Lighting
double asp=1;     //  Aspect ratio
double dim=50.0;  //  Size of world
int lightFollow=0;//  Should the light follow the character
// Light values
int one       =   1;  // Unit value
int distance  =  15;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =   5;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shinyvec[1];    // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   3;  // Elevation of light

int i=0, o=0, p=0;







/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
  double lightFollowPos[3] = {0,0,0};
  const double len=2.0;  //  Length of axes
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);

   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (mode == FIRST_PERSON){
     double dist = 3;
     btTransform characterTransform = worldCharacter->getWorldTransform();
     double x = characterTransform.getOrigin().getX();
     double y = characterTransform.getOrigin().getY();
     double z = characterTransform.getOrigin().getZ();
  
     double Ex = x-dist*Cos(fpth);
     double Ey = y+1;
     double Ez = z+dist*Sin(fpth);

     lightFollowPos[0] = Ex;
     lightFollowPos[1] = Ey+1;
     lightFollowPos[2] = Ez;

     gluLookAt(Ex,Ey,Ez, x,y,z, 0, Cos(ph),0);
   }
   else if (mode)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }

   //  Flat or smooth shading
   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   drawSky();
   
   //  Translate intensity to color vectors
   float Ambient[]   = {0.01f*ambient, 0.01f*ambient, 0.01f*ambient, 1.0f};
   float Diffuse[]   = {0.01f*diffuse ,0.01f*diffuse ,0.01f*diffuse ,1.0f};
   float Specular[]  = {0.01f*specular,0.01f*specular,0.01f*specular,1.0f};
   //  Light position
   float Position[4];
   if(lightFollow){
     Position[0] = lightFollowPos[0];
     Position[1] = lightFollowPos[1];
     Position[2] = lightFollowPos[2];
     Position[3] = 1.0;
   }else{
     Position[0] = distance*Cos(zh);
     Position[1] = ylight;
     Position[2] = distance*Sin(zh);
     Position[3] = 1.0;
   }
   //  Draw light position as ball (still no lighting here)
   glColor3f(1,1,1);
   sphere(Position[0],Position[1],Position[2] , 0.1, shinyvec, emission);
   //  OpenGL should normalize normal vectors
   glEnable(GL_NORMALIZE);
   //  Enable lighting
   glEnable(GL_LIGHTING);
   //  Location of viewer for specular calculations
   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
   //  glColor sets ambient and diffuse color materials
   glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);
   //  Enable light 0
   glEnable(GL_LIGHT0);
   //  Set ambient, diffuse, specular components and position of light 0
   glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
   glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
   glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
   glLightfv(GL_LIGHT0,GL_POSITION,Position);
   

   //  Draw scene
   drawStaticWorld();
   drawDynamicWorld();

   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }

   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   stepSim();
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
  if(mode == FIRST_PERSON){
    btVector3 move(0,0,0);
    // Turn character right
    if (key == GLUT_KEY_RIGHT){
      move.setZ(100*Cos(fpth));
      move.setX(100*Sin(fpth));
    }
    // Turn character left
    else if (key == GLUT_KEY_LEFT){
      move.setZ(-100*Cos(fpth));
      move.setX(-100*Sin(fpth));
    }
    //  Move forward
    else if (key == GLUT_KEY_UP){
      move.setX(100*Cos(-fpth));
      move.setZ(100*Sin(-fpth));
    }
    //  Move backward
    else if (key == GLUT_KEY_DOWN){
      move.setX(-100*Cos(-fpth));
      move.setZ(-100*Sin(-fpth));
    }
    worldCharacter->applyCentralForce(move);
    
  }
  else{
    //  Right arrow key - increase angle by 5 degrees
    if (key == GLUT_KEY_RIGHT)
      th += 5;
    //  Left arrow key - decrease angle by 5 degrees
    else if (key == GLUT_KEY_LEFT)
      th -= 5;
    //  Up arrow key - increase elevation by 5 degrees
    else if (key == GLUT_KEY_UP)
      ph += 5;
    //  Down arrow key - decrease elevation by 5 degrees
    else if (key == GLUT_KEY_DOWN)
      ph -= 5;
    //  PageUp key - increase dim
    else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
    //  PageDown key - decrease dim
    else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
  }
  //  Keep angles to +/-360 degrees
  th %= 360;
  ph %= 360;
  fpth %= 360;
  //  Update projection
  Project(mode?fov:0,asp,dim);
  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;
   //Switch between first person and not
   else if (ch=='f' || ch=='F')
     mode= mode==2?1:2;
   // rotate in FP
   else if ('a' == ch || 'A' == ch){
     btVector3 vert(0,1,0);
     fpth+=5;
   }
   else if ('d' == ch || 'D' == ch){
     btVector3 vert(0,1,0);
     fpth-=5;
   }
   // Should the light follow the player
   else if ('l' == ch || 'L' == ch){
     lightFollow = 1 - lightFollow;
   }
   // light circle radius
   else if ('k' == ch || 'K' == ch){
     distance = 5==distance?15:
       15==distance?30:5;
   }
   //  Translate shininess power to value (-1 => 0)
   shinyvec[0] = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(mode?fov:0,asp,dim);
   //  Animate if requested
   glutIdleFunc(move?idle:NULL);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(mode?fov:0,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(400,400);
   glutCreateWindow("David Baird");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);

   skyboxInit();
   initBullet();
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
