#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "bullet3-2.83.6/src/btBulletDynamicsCommon.h"

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

btConvexHullShape* triangularPrismShape(double sx, double sy, double sz);
btCompoundShape* bicycleShape();
btRigidBody* createRigidBody(btCollisionShape* shape, float mass, btVector3 pos);

// Objects
extern btCollisionShape* worldGroundShape;
extern btRigidBody* worldGround;
extern btCollisionShape* worldCharacterShape;
extern btRigidBody* worldCharacter;

extern btCollisionShape* triangularBaseShape1;
extern btRigidBody* triangularBase1;
extern btCollisionShape* triangularBaseShape2;
extern btRigidBody* triangularBase2;

static const int numBicycles = 2;
extern btCollisionShape* bicycleShapes[1];
extern btRigidBody* bicycles[numBicycles];

static const int numCylinders = 2;
extern btCollisionShape* cylinderShapes[2];
extern btRigidBody* cylinders[numCylinders];

static const int numBoxes = 4;
extern btCollisionShape* boxShapes[4];
extern btRigidBody* boxes[numBoxes];

static const int numSpheres = 8;
extern btCollisionShape* sphereShapes[2];
extern btRigidBody* spheres[numSpheres];

static const int numCones = 8;
extern btCollisionShape* coneShapes[2];
extern btRigidBody* cones[numCones];

static const int numTriangularPrisms = 4;
extern btCollisionShape* triangularPrismShapes[1];
extern btRigidBody* triangularPrisms[numTriangularPrisms];

#endif
