#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <map>

#include <json.hpp>

#include <render/mesh.hpp>
#include <render/sprite2d.hpp>
#include <render/light.hpp>

using json = nlohmann::json;

namespace Core {

    class MapLoader {

    public:
        
        std::map<std::string, Render::Mesh*> objects_mesh;
        std::map<std::string, Render::Sprite2D*> objects_sprite;
        std::map<std::string, Render::DirectionalLight*> objects_dlight;

        MapLoader(std::string path);
        void draw();

    };

}