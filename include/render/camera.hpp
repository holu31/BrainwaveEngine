#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace Core {

    class Camera {

    public:
        static Camera *current;

	float fov = 90.0f;
        float near = 0.01f;
        float far = 100.0f;

        glm::vec3 pos = glm::vec3(0.0f);
        glm::vec3 rot = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);

        Camera();

        glm::mat4 projMatGet();
        glm::mat4 viewMatGet();

    };

}