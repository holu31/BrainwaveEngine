#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

namespace Render {

    class Shaders {

        public:
            std::vector<char> vertCode;
            std::vector<char> fragCode;

            int program = glCreateProgram();
            int vShader = glCreateShader(GL_VERTEX_SHADER);
            int fShader = glCreateShader(GL_FRAGMENT_SHADER);

            Shaders(const std::string &vertFilepath,
                    const std::string &fragFilepath);
            ~Shaders() {}
            void Bind();
            void Unbind();
            void setUniform(
                std::string uniform, glm::mat4 value
            );
            int getULoc(std::string uname);
            void setUInt(std::string uname, int value);

        private:

            void setSource(int id, const char *source);
            static std::vector<char> readFile(const std::string& filepath);
    };

};
