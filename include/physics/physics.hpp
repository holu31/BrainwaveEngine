#pragma once

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

namespace Physics {

    class Physics {

    btRigidBody *obj;
    bool applyForce = false;

    public:
        int steps = 7;

        static btDynamicsWorld *dynamicsWorld;

        Physics();
        ~Physics();
        
    };

}