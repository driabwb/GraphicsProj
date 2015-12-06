// Functions that well handle the physics simulation for the game


#include "physics.h"
#include "GLDebugDrawer.h"

static btDefaultCollisionConfiguration* collisionConfiguration;
static btCollisionDispatcher* dispatcher;
static btBroadphaseInterface* overlappingPairCache;
static btSequentialImpulseConstraintSolver* solver;
btDiscreteDynamicsWorld* dynamicsWorld;

btCollisionShape* worldGroundShape;
btRigidBody* worldGround;
btCollisionShape* worldCharacterShape;
btRigidBody* worldCharacter;

btCollisionShape* triangularBaseShape1;
btRigidBody* triangularBase1;
btCollisionShape* triangularBaseShape2;
btRigidBody* triangularBase2;

btCollisionShape* bicycleShapes[1];
btRigidBody* bicycles[numBicycles];

btCollisionShape* cylinderShapes[2];
btRigidBody* cylinders[numCylinders];

btCollisionShape* boxShapes[5];
btRigidBody* boxes[numBoxes];

btCollisionShape* sphereShapes[2];
btRigidBody* spheres[numSpheres];

btCollisionShape* coneShapes[2];
btRigidBody* cones[numCones];

btCollisionShape* triangularPrismShapes[1];
btRigidBody* triangularPrisms[numTriangularPrisms];

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
  if(dynamicsWorld->getDebugDrawer()==NULL){
    btIDebugDraw* debugDrawer = new GLDebugDrawer();
    dynamicsWorld->setDebugDrawer(debugDrawer);
  }
  dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
  
  fflush(stdout);
  //dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe);

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
  btVector3 localInertia(0,0,0);
  btTransform transform;
  btDefaultMotionState* myMotionState;
  
  // Create the ground
  worldGroundShape = new btBoxShape(btVector3(50,0.1,50));
  worldGround = createRigidBody(worldGroundShape, mass, btVector3(0,0,0));

  // Create triangular bases
  btQuaternion worldRotation(btVector3(1,0,0), -90*PI/180.0);
  btQuaternion rot180(btVector3(0,0,1), 180*PI/180.0);
  btQuaternion fullRot(0,0.7,0.7,0);
  triangularBaseShape1 = triangularPrismShape(1,1.3,1.2);
  transform.setIdentity();
  transform.setOrigin(btVector3(2,0,2.5));
  transform.setRotation(worldRotation);
  
  myMotionState = new btDefaultMotionState(transform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo1(mass,myMotionState,triangularBaseShape1,localInertia);
  triangularBase1 = new btRigidBody(rbInfo1);

  triangularBaseShape2 = triangularPrismShape(1,1.3,1);
  transform.setIdentity();
  transform.setOrigin(btVector3(2,0,-4.5));
  transform.setRotation(fullRot);

  myMotionState = new btDefaultMotionState(transform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo2(mass,myMotionState,triangularBaseShape2,localInertia);
  triangularBase2 = new btRigidBody(rbInfo2);

  // The scene's cylinders
  
  cylinderShapes[0] = new btCylinderShape(btVector3(0.5,1,0.5));
  cylinderShapes[1] = new btCylinderShape(btVector3(0.5,1,0.5));

  cylinders[0] = createRigidBody(cylinderShapes[0], mass, btVector3(2,1,0));
  cylinders[1] = createRigidBody(cylinderShapes[1], mass, btVector3(2,1,-2));  
  

  // The scene's boxes
  boxShapes[0] = new btBoxShape(btVector3(21,1,0.5)); // top and bottom bounding walls
  boxShapes[1] = new btBoxShape(btVector3(21,1,0.5));
  boxShapes[2] = new btBoxShape(btVector3(0.5,1,21)); // left and right bounding walls
  boxShapes[3] = new btBoxShape(btVector3(0.5,1,21));
  boxShapes[4] = new btBoxShape(btVector3(1,0.25,3));

  boxes[0] = createRigidBody(boxShapes[0], mass, btVector3(0,0,20.5));
  boxes[1] = createRigidBody(boxShapes[1], mass, btVector3(0,0,-20.5));
  boxes[2] = createRigidBody(boxShapes[2], mass, btVector3(20.5,0,0));
  boxes[3] = createRigidBody(boxShapes[3], mass, btVector3(-20.5,0,0));
  boxes[4] = createRigidBody(boxShapes[4], mass, btVector3(2,1,-1));
  
  // Create a bicycle
  bicycleShapes[0] = bicycleShape();

  bicycles[0] = createRigidBody(bicycleShapes[0], mass, btVector3(2,3.5,0), 90);
  bicycles[1] = createRigidBody(bicycleShapes[0], mass, btVector3(-15,1,-15));
  
  // The scene's spheres
  sphereShapes[0] = new btSphereShape(1);
  sphereShapes[1] = new btSphereShape(2);

  spheres[0] = createRigidBody(sphereShapes[0], mass, btVector3(10, 0, 10));
  spheres[1] = createRigidBody(sphereShapes[0], mass, btVector3(10, 0, -10));
  spheres[2] = createRigidBody(sphereShapes[0], mass, btVector3(-10, 0, 10));
  spheres[3] = createRigidBody(sphereShapes[0], mass, btVector3(-10, 0, -10));
  spheres[4] = createRigidBody(sphereShapes[1], mass, btVector3(0, 0, 10));
  spheres[5] = createRigidBody(sphereShapes[1], mass, btVector3(0, 0, -10));
  spheres[6] = createRigidBody(sphereShapes[1], mass, btVector3(10, 0, 0));
  spheres[7] = createRigidBody(sphereShapes[1], mass, btVector3(-10, 0, 0));

  // The scene's cones
  coneShapes[0] = new btConeShape(1, 1);
  coneShapes[1] = new btConeShape(1, 2);
  
  cones[0] = createRigidBody(coneShapes[0], mass, btVector3(15,0.5,5));
  cones[1] = createRigidBody(coneShapes[0], mass, btVector3(15,0.5,-5));
  cones[2] = createRigidBody(coneShapes[0], mass, btVector3(15,0.5,15));
  cones[3] = createRigidBody(coneShapes[0], mass, btVector3(15,0.5,-15));
  cones[4] = createRigidBody(coneShapes[1], mass, btVector3(15,0.5,10));
  cones[5] = createRigidBody(coneShapes[1], mass, btVector3(15,0.5,-10));
  cones[6] = createRigidBody(coneShapes[0], mass, btVector3(-15,0.5,5));
  cones[7] = createRigidBody(coneShapes[0], mass, btVector3(-15,0.5,-5));

  // Triangular Prisms
  btQuaternion triangularPrismRot(btVector3(1,0,0), 150*PI/180.0);
  triangularPrismShapes[0] = triangularPrismShape(1,1,1);

  triangularPrisms[0] = createRigidBody(triangularPrismShapes[0], mass, btVector3(5,0,15));
  triangularPrisms[1] = createRigidBody(triangularPrismShapes[0], mass, btVector3(-5,0,15));
  triangularPrisms[2] = createRigidBody(triangularPrismShapes[0], mass, btVector3(5,0,-15));
  triangularPrisms[3] = createRigidBody(triangularPrismShapes[0], mass, btVector3(-5,0,-15));

  for(int i = 0; i<numTriangularPrisms; i++){
    triangularPrisms[i]->getWorldTransform().setRotation(triangularPrismRot);
  }
  
  //add the bodies to the dynamics world
  dynamicsWorld->addRigidBody(worldGround);
  dynamicsWorld->addRigidBody(triangularBase1);
  dynamicsWorld->addRigidBody(triangularBase2);  

  int i;
  // Add Cylinders
  for(i=0; i<numCylinders; i++){
    dynamicsWorld->addRigidBody(cylinders[i]);
  }

  // Add boxes
  for(i=0; i<numBoxes; i++){
    dynamicsWorld->addRigidBody(boxes[i]);
  }
  
  // Add spheres
  for(i=0; i<numSpheres; i++){
    dynamicsWorld->addRigidBody(spheres[i]);
  }

  // Add Cones
  for(i=0; i<numCones; i++){
    dynamicsWorld->addRigidBody(cones[i]);
  }

  // Add Triangular Prisms
  for(i=0; i<numTriangularPrisms; i++){
    dynamicsWorld->addRigidBody(triangularPrisms[i]);
  }

  // Add Bicycles
  for(i=0; i<numBicycles; i++){
    dynamicsWorld->addRigidBody(bicycles[i]);
  }

}

void createDynamicObjects(){
  float mass = 1.f;
  btDefaultMotionState* myMotionState;
  
  // Create the player construct
  worldCharacterShape = new btBoxShape(btVector3(0.2, 0.2, 0.2));
  btTransform characterTransform;
  characterTransform.setIdentity();
  characterTransform.setOrigin(btVector3(0,5,0));
  btVector3 localInertia(0,0,0);
  worldCharacterShape->calculateLocalInertia(mass, localInertia);

  //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  myMotionState = new btDefaultMotionState(characterTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,worldCharacterShape,localInertia);
  rbInfo.m_linearDamping = 0.5;
  worldCharacter = new btRigidBody(rbInfo);
  worldCharacter->setActivationState(DISABLE_DEACTIVATION);
  dynamicsWorld->addRigidBody(worldCharacter);
  
}

bool isCharacterOnObject(){


  btTransform transform = worldCharacter->getWorldTransform();
  btVector3 from(transform.getOrigin().getX(), transform.getOrigin().getY(), transform.getOrigin().getZ());
  btVector3 to = from - btVector3(0,0.3, 0);
  btCollisionWorld::ClosestRayResultCallback res(from, to);

  dynamicsWorld->rayTest(from,to,res);

  return res.hasHit();
}

void stepSim(){
  dynamicsWorld->stepSimulation(1.f/60.f,10);

  /*
    For Additional Debugging information

  btCollisionObject* obj;
  btRigidBody* body;
  btTransform trans;
  obj = worldCharacter;
  body = btRigidBody::upcast(obj);
  if (body && body->getMotionState())
  {
    body->getMotionState()->getWorldTransform(trans);
      
  } else
  {
    trans = obj->getWorldTransform();
  }
  */

}

btConvexHullShape* triangularPrismShape(double sx=1.0, double sy=1.0, double sz=1.0){
  btConvexHullShape* prism = new btConvexHullShape();
  btVector3 pt1(1,-1,0), pt2(1,1,0), pt3(1,0.5,1), pt4(-1,-1,0), pt5(-1,1,0), pt6(-1,0.5,1);
  prism->addPoint(pt1);
  prism->addPoint(pt2);
  prism->addPoint(pt3);
  prism->addPoint(pt6);
  prism->addPoint(pt4);
  prism->addPoint(pt5);
  prism->addPoint(pt6);
  prism->addPoint(pt5);
  prism->addPoint(pt2);
  prism->addPoint(pt5);
  prism->addPoint(pt4);
  prism->addPoint(pt1);
  prism->addPoint(pt3);

  btVector3 scaling(sx,sz,sy);
  prism->setLocalScaling(scaling);

  return prism;
}

btCompoundShape* bicycleShape(){
  btCompoundShape* bicycle = new btCompoundShape();
  btCylinderShapeZ* frontWheel = new btCylinderShapeZ(btVector3(1.6,1.6,0.125));
  btCylinderShapeZ* backWheel = new btCylinderShapeZ(btVector3(0.5,0.5,0.125));
  //btBoxShape* handlebars = new btBoxShape(bvVector());
  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(btVector3(0,0,0));
  bicycle->addChildShape(transform, frontWheel);
  transform.setIdentity();
  transform.setOrigin(btVector3(4.75742/2,-1,0));
  bicycle->addChildShape(transform, backWheel);

  return bicycle;
}

btRigidBody* createRigidBody(btCollisionShape* shape, float mass, btVector3 pos, double ry){
  btVector3 localInertia(0,0,0);
  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(pos);
  btQuaternion rot(btVector3(0,1,0), ry*PI/180.0);
  transform.setRotation(rot);
  btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);
  return new btRigidBody(rbInfo);
}
