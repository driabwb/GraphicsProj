// Drawer for debugging collision shapes

#include "GLDebugDrawer.h"
#include "bullet3-2.83.6/src/btBulletDynamicsCommon.h"
#include "bullet3-2.83.6/src/LinearMath/btIDebugDraw.h"
#include "CSCIx229.h"
#include <cstdio>

GLDebugDrawer::GLDebugDrawer() : m_debugMode(0) { }

void    GLDebugDrawer::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
{
  //      if (m_debugMode > 0)
  {
    glPushMatrix();
    {
      //glColor4f(color.getX(), color.getY(), color.getZ(), 1.0f);
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      glBegin(GL_LINES);
      glVertex3f(from.getX(),from.getY(), from.getZ());
      glVertex3f(to.getX(),to.getY(), to.getZ());
      glEnd();
    }
    glPopMatrix();
  }
}

void    GLDebugDrawer::setDebugMode(int debugMode)
{
  m_debugMode = debugMode;
}

void    GLDebugDrawer::draw3dText(const btVector3& location,const char* textString)
{
  //glRasterPos3f(location.x(),  location.y(),  location.z());
  //BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),textString);
}

void    GLDebugDrawer::reportErrorWarning(const char* warningString)
{
  printf("%s", warningString);
}

void    GLDebugDrawer::drawContactPoint(const btVector3& pointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color)
{
  {
    //btVector3 to=pointOnB+normalOnB*distance;
    //const btVector3&from = pointOnB;
    //glColor4f(color.getX(), color.getY(), color.getZ(), 1.0f);

    //GLDebugDrawer::drawLine(from, to, color);

    //glRasterPos3f(from.x(),  from.y(),  from.z());
    //char buf[12];
    //sprintf(buf," %d",lifeTime);
    //BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
  }
}
