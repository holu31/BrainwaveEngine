#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>

namespace Render {

    ///
    /// \brief Class used to render lights and shadows
    ///

    class DirectionalLight {

    public:
        static DirectionalLight *current;

        float specularStrength;
        float ambientStrength;
        glm::vec3 lightColor;

        glm::vec3 pos = glm::vec3(0.0f);

        ///
        /// \brief Function to initialize a class
        /// \param lightColor directional light color
        /// \param ambientStrength ambient light power/strength
        ///
        DirectionalLight(glm::vec3 lightColor = glm::vec3(1.0f), float ambientStrength = 0.4f,
                float specularStrength = 0.5f);

    };
    extern std::vector<DirectionalLight*> lights;

}