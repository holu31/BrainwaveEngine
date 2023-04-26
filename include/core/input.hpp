#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

namespace Core {

    class Input {

        glm::vec2 lastMousePos = glm::vec2(0.0f);
        GLFWwindow *m_pWindow;

    public:

        enum Keys {
            KEY_A = 65,
            KEY_D = 68,
            KEY_S = 83,
            KEY_W = 87,

            KEY_ESCAPE = 256,
        };

        Input(GLFWwindow *window);

        bool pressed(int key);

        void cursorLock();
        void cursorHide();
        void cursorShow();

        glm::vec2 mousePosition();
        glm::vec2 mouseMotion();

        glm::vec3 getAxis(int key1, int key2,
                        int key3, int key4);

    };

}