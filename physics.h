#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "bullet3-2.83.6/headers/btBulletDynamicsCommon.h"

// Convenience Macros
// From Bullet to my Coordinates
#define getXFromBullet(transform) transform.getOrigin().getX()
#define getYFromBullet(transform) -1*transform.getOrigin().getZ()
#define getZFromBullet(transform) transform.getOrigin().getY()
// From my Coordinates to Bullet
#define getXToBullet(x,y,z) x
#define getYToBullet(x,y,z) z
#define getZToBullet(x,y,z) -y

// Functions
void initBullet();
void createSceneObjects();
void createStaticObjects();
void createDynamicObjects();
void stepSim();
void cleanUp();

// Objects
extern btCollisionShape* worldGroundShape;
extern btRigidBody* worldGround;
extern btCollisionShape* worldCharacterShape;
extern btRigidBody* worldCharacter;


#endif
