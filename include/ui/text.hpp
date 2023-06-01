#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <map>

#include <render/shaders.hpp>

namespace UI {

    class Text {

        struct Character {
            unsigned int TextureID;
            glm::ivec2 Size;
            glm::ivec2 Bearing;
            long int Advance;
        };

        std::map<char, Character> Characters;

        FT_Library ft;
        FT_Face face;

        std::string text;
        Render::Shaders *shader;

    public:
        Text(std::string text, std::string fontPath);
        void draw();

        glm::vec2 pos = glm::vec2(0.0f);
        glm::vec2 scale = glm::vec2(1.0f);
        glm::vec3 color = glm::vec3(0.0f);

    };

}