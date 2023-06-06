#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <render/mesh.hpp>
#include <render/shaders.hpp>
#include <core/input.hpp>
#include <core/config.hpp>

#include <iostream>
#include <map>
#include <stdint.h>

#include <physics/physics.hpp>

#define LOG(fun, type, log) \
        printf("%s:%s:[%s]: %s\n", #fun, __FILE__, type, log); \
    fun;

namespace Core {

    class Engine {

        GLFWwindow* m_window;
        float m_prevDeltaTime;
        Input *input;

        Physics::Physics *physics;

        public:

            Engine(Core::Config config);
            ~Engine();

            void _process(float deltaTime);
            void _start();
            void _exit_window();
            void _input(int key);
    };

};
