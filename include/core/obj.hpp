#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>
#include <vector>

#include <render/mesh.hpp>
#include <render/shaders.hpp>

namespace Core {

    class ObjLoader {

    public:

        std::vector<float> positions;
        std::vector<int> indices;
        std::vector<float> normals;
        std::vector<float> uv;

        ObjLoader(std::string path);
    };

}