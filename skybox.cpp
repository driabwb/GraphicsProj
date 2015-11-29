// Draw Skybox

#include "CSCIx229.h"
#include "skybox.h"

unsigned int skyboxTex;

void skyboxInit(){
  // init texture
  //skyboxTex = LoadTexBMP("textures/skybox.bmp");
}

void drawSkybox(double dim){

  glColor3f(1,0,0);
  glRotatef(-90, 1,0,0);

  /* Texturing
  // Turn on textures
  glEnable(GL_TEXTURE_2D);

  // GL_Modulate mixes underlying color/lighting to the applied texture
  glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);

  // Select the skybox texture
  glBindTexture(GL_TEXTURE_2D, skyboxTex);
  */
  glBegin(GL_QUADS);

  // Left
  //glTexCoord2f(0,0.2461);
  glVertex3f(-dim,-dim,-dim);
  //glTexCoord2f(0.2461,0.2461);
  glVertex3f(-dim,dim,-dim);
  //glTexCoord2f(0.2461,0.7539);
  glVertex3f(-dim,dim,dim);
  //glTexCoord2f(0,0.7539);
  glVertex3f(-dim,-dim,dim);

  // Right
  //glTexCoord2f(1,0.2461);
  glVertex3f(dim,-dim,-dim);
  //glTexCoord2f(0.7539,0.2461);
  glVertex3f(dim,-dim,dim);
  //glTexCoord2f(0.7539,0.27539);
  glVertex3f(dim,dim,dim);
  //glTexCoord2f(1,0.7539);
  glVertex3f(dim,dim,-dim);

  // Front
  glVertex3f(-dim,dim,-dim);
  glVertex3f(dim,dim,-dim);
  glVertex3f(dim,dim,dim);
  glVertex3f(-dim,dim,dim);

  // Back
  glVertex3f(-dim,-dim,-dim);
  glVertex3f(-dim,-dim,dim);
  glVertex3f(dim,-dim,dim);
  glVertex3f(dim,-dim,-dim);

  // Top
  glVertex3f(-dim,-dim,dim);
  glVertex3f(-dim,dim,dim);
  glVertex3f(dim,dim,dim);
  glVertex3f(dim,-dim,dim);

  // Bottom
  glVertex3f(-dim,-dim,-dim);
  glVertex3f(dim,-dim,-dim);
  glVertex3f(dim,dim,-dim);
  glVertex3f(-dim,dim,-dim);

  glEnd();

  glDisable(GL_TEXTURE_2D);
}
