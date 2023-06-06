#include <physics/physics.hpp>
#include <core/engine.hpp>

Physics::Physics::Physics() {
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
    LOG(dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration), \
        "INFO", "creating physics world");
    LOG(dynamicsWorld->setGravity(btVector3(0.0f, -10.0f, 0.0f)), "INFO", "setting default gravity into world");
}

Physics::Physics::~Physics(){
    delete dynamicsWorld;
}

btDynamicsWorld *Physics::Physics::dynamicsWorld = nullptr;