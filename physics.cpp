// Functions that well handle the physics simulation for the game


#include "physics.h"

static btDefaultCollisionConfiguration* collisionConfiguration;
static btCollisionDispatcher* dispatcher;
static btBroadphaseInterface* overlappingPairCache;
static btSequentialImpulseConstraintSolver* solver;
static btDiscreteDynamicsWorld* dynamicsWorld;

btCollisionShape* worldGroundShape;
btRigidBody* worldGround;
btCollisionShape* worldCharacterShape;
btRigidBody* worldCharacter;


// Initialize bullet
void initBullet(){
  ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
  collisionConfiguration = new btDefaultCollisionConfiguration();
  ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
  dispatcher = new btCollisionDispatcher(collisionConfiguration);

  ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
  overlappingPairCache = new btDbvtBroadphase();

  ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
  solver = new btSequentialImpulseConstraintSolver;

  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);

  /*
  // Rotate the coordinates so that z is up.
  btTransform worldTransform();
  worldTransform.setIdentity();
  btQuaternion worldQuaternion(btVector3(1,0,0), -90);
  worldTransform.setRotation(worldQuaternion);
  */
  
  // Sets the gravity for the world. Note that bullet does not have the general rotation I set up for the Graphics thus up = positive y
  dynamicsWorld->setGravity(btVector3(0,-10,0));

  createSceneObjects();
  
}

void cleanUp(){
  
}

void createSceneObjects(){
  createStaticObjects();
  createDynamicObjects();
}

void createStaticObjects(){
  float mass = 0.f;

  // Create the ground
  worldGroundShape = new btBoxShape(btVector3(50,0.1,50));
  btTransform groundTransform;
  groundTransform.setIdentity();
  groundTransform.setOrigin(btVector3(0,0,0));
  btVector3 localInertia(0,0,0);

  //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,worldGroundShape,localInertia);
  worldGround = new btRigidBody(rbInfo);

  //add the body to the dynamics world
  dynamicsWorld->addRigidBody(worldGround);

  
  
}

void createDynamicObjects(){
  float mass = 1.f;

  
  // Create the player construct
  worldCharacterShape = new btBoxShape(btVector3(0.1, 0.1, 0.1));
  btTransform characterTransform;
  characterTransform.setIdentity();
  characterTransform.setOrigin(btVector3(0,5,0));
  btVector3 localInertia(0,0,0);
  worldCharacterShape->calculateLocalInertia(mass, localInertia);

  //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* myMotionState = new btDefaultMotionState(characterTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,worldCharacterShape,localInertia);
  worldCharacter = new btRigidBody(rbInfo);

  dynamicsWorld->addRigidBody(worldCharacter);
  
}


void stepSim(){
  dynamicsWorld->stepSimulation(1.f/60.f,10);

  //print positions of all objects
  for (int j=dynamicsWorld->getNumCollisionObjects()-1; j>=1 ;j--)
    {
      btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
      btRigidBody* body = btRigidBody::upcast(obj);
      btTransform trans;
      if (body && body->getMotionState())
	{
	  body->getMotionState()->getWorldTransform(trans);
	  
	} else
	{
	  trans = obj->getWorldTransform();
	}
      printf("world pos object %d = %f,%f,%f\n",j,float(trans.getOrigin().getX()),float(trans.getOrigin().getY()),float(trans.getOrigin().getZ()));
      obj = worldCharacter;
      body = btRigidBody::upcast(obj);
      if (body && body->getMotionState())
	{
	  body->getMotionState()->getWorldTransform(trans);
	  
	} else
	{
	  trans = obj->getWorldTransform();
	}
      
      printf("world pos object %s = %f,%f,%f\n","character",float(trans.getOrigin().getX()),float(trans.getOrigin().getY()),float(trans.getOrigin().getZ()));
    }
}
