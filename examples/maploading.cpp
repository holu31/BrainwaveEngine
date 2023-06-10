#include <iostream>

#include <core/engine.hpp>
#include <core/maploader.hpp>

#include <render/camera.hpp>

#include <cstdlib>

Core::MapLoader *map;
Render::Camera *camera;

void Core::Engine::_start(){
    camera = new Render::Camera();
    map = new Core::MapLoader("resources/maps/test_map.json");

    camera->pos = glm::vec3(0.0f, 0.0f, 10.0f);
}

void Core::Engine::_process(float deltaTime){
    map->draw();
}

void Core::Engine::_input(int key){
    std::cout << key << std::endl;
}

void Core::Engine::_exit_window(){

}

auto main() -> int {
    Core::Engine engine(Core::Config(
        "MapLoading",
        900,
        480,
        2,
        false));
    return 0;
}