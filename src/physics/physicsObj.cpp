#include <physics/physicsObj.hpp>
#include <core/engine.hpp>

#include <iostream>


Physics::PhysicsObject::PhysicsObject(
    btCollisionShape *shape, btMotionState *transform, float mass,
        glm::vec3 inertia, float restitution)
{
    LOG(this->Init(shape, transform, mass, inertia, restitution), \
        "INFO", "initializing physics object");
}

Physics::PhysicsObject::PhysicsObject(
    CollisionsType type, glm::vec3 scale, float mass)
{
    if(type == COLLISION_CUBE){
        btCollisionShape* boxShape = new btBoxShape(btVector3(scale.x, scale.y, scale.z));
        btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(
            btQuaternion(0, 0, 0, 1),
            btVector3(0, 0, 0)));
        LOG(this->Init(
            boxShape,
            motionState,
            mass,
            glm::vec3(0.0f),
            .25f
        ), "INFO", "initializing physics object");
    }
}

void Physics::PhysicsObject::Init(
    btCollisionShape *shape, btMotionState *transform, float mass,
            glm::vec3 inertia, float restitution)
{
    this->m_pShape = shape;
    this->m_pTransform = transform;
    this->mass = mass;
    this->inertia = inertia;
    this->restitution = restitution;

    LOG(btRigidBody::btRigidBodyConstructionInfo rbConstrInfo(btScalar(mass), transform, shape), \
        "INFO", "configuration physics object");
    rbConstrInfo.m_restitution = restitution;
    LOG(rb = new btRigidBody(rbConstrInfo), "INFO", "creating rigidbody");
    rb->forceActivationState(DISABLE_DEACTIVATION);
    LOG(Physics::dynamicsWorld->addRigidBody(rb), "INFO", "added physics object to dynamics world");
}