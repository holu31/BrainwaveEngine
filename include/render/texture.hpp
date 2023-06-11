#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>


namespace Render {

    ///
    /// \brief Class for texturing various objects, models and maps
    ///

    class Texture {
    
    glm::ivec2 size;
    int channels;
    unsigned char *data;

    unsigned int id;

    public:

        ///
        ///
        /// \param texturePath Full path from the game folder to download the texture
        ///
        Texture(std::string texturePath);
        
        ///
        /// \brief Function to import texture into model, object
        ///
        void import();
        void bind();
        void unbind();

    };
    
}
