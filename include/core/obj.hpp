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

    enum ModelType {
        MODEL_BWM,
        MODEL_OBJ,
    };

    class ObjLoader {

        void loadBwm(std::string path);
        void loadObj(std::string path);

    public:

        std::vector<float> positions;
        std::vector<int> indices;
        std::vector<float> normals;
        std::vector<float> uv;

        ObjLoader(Core::ModelType type, std::string path);
    };

}