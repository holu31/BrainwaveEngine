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

    ///
    /// \brief The main class used to draw the window and initial project settings
    ///

    class Engine {

        GLFWwindow* m_window;
        float m_prevDeltaTime;
        Input *input;

        Physics::Physics *physics;

        public:

            ///
            /// \brief Function to initialize the main class
            /// \param config parameter for the initial configuration of the main class
            ///

            Engine(Core::Config config);
            ~Engine();

            ///
            /// \brief Function for rendering, logistics and more. Called every frame
            /// \param deltaTime time elapsed since the last frame
            ///
            void _process(float deltaTime);

            ///
            /// \brief Starting point of interaction with the main class and its children
            ///
            void _start();

            ///
            /// \brief Function to listen for exit from window
            ///
            void _exit_window();
            
            ///
            /// \brief Function to listen for keystrokes
            /// \param key Number of pressed key
            /// \warning This feature is under development
            ///
            void _input(int key);
    };

};
