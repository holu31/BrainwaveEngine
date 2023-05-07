#include <physics/physicsObj.hpp>
#include <iostream>


Physics::PhysicsObject::PhysicsObject(
    btCollisionShape *shape, btMotionState *transform, float mass,
        glm::vec3 inertia, float restitution)
{
    this->Init(shape, transform, mass, inertia, restitution);
}

Physics::PhysicsObject::PhysicsObject(
    CollisionsType type, glm::vec3 scale, float mass)
{
    if(type == COLLISION_CUBE){
        btCollisionShape* boxShape = new btBoxShape(btVector3(scale.x, scale.y, scale.z));
        btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(
            btQuaternion(0, 0, 0, 1),
            btVector3(0, 0, 0)));
        this->Init(
            boxShape,
            motionState,
            mass,
            glm::vec3(0.0f),
            .25f
        );
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

    btRigidBody::btRigidBodyConstructionInfo rbConstrInfo(btScalar(mass), transform, shape);
    rbConstrInfo.m_restitution = restitution;
    rb = new btRigidBody(rbConstrInfo);
    rb->forceActivationState(DISABLE_DEACTIVATION);
    Physics::dynamicsWorld->addRigidBody(rb);
}