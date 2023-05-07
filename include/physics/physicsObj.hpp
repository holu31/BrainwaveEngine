#pragma once

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include <glm/glm.hpp>

#include <physics/physics.hpp>

namespace Physics {

    enum CollisionsType {
        COLLISION_CUBE,
    };

    class PhysicsObject {

        void Init(btCollisionShape *shape, btMotionState *transform, float mass,
            glm::vec3 inertia, float restitution);

    public:
        btCollisionShape* m_pShape;
        btMotionState* m_pTransform;
        float mass;
        glm::vec3 inertia;
        float restitution;
        btRigidBody* rb;

        PhysicsObject(btCollisionShape *shape, btMotionState *transform, float mass,
            glm::vec3 inertia, float restitution = 0.25f);
        PhysicsObject(CollisionsType type, glm::vec3 scale, float mass = 0.0f);

    };

}