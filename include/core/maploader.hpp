#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <map>

#include <json.hpp>

#include <render/mesh.hpp>

using json = nlohmann::json;

namespace Core {

    class MapLoader {

    public:

        std::map<std::string, Render::Mesh*> objects;

        MapLoader(std::string path);
        void draw();

    };

}