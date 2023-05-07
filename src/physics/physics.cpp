#include <physics/physics.hpp>


Physics::Physics::Physics() {
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0.0f, -10.0f, 0.0f));
}

Physics::Physics::~Physics(){
    delete dynamicsWorld;
}

btDynamicsWorld *Physics::Physics::dynamicsWorld = nullptr;