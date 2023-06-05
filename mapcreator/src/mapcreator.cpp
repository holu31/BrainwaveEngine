#include <iostream>

#include <core/engine.hpp>
#include <render/camera.hpp>

#include <cstdlib>

Render::Camera *camera;

void Core::Engine::_start(){
    camera = new Render::Camera();

    camera->pos = glm::vec3(0.0f, 0.0f, 3.0f);
}

void Core::Engine::_process(float deltaTime){
}

void Core::Engine::_input(int key){
    std::cout << key << std::endl;
}

void Core::Engine::_exit_window(){
}

auto main() -> int {
    Core::Engine engine(Core::Config(
        "MapCreator",
        900,
        480,
        2,
        false));
    return 0;
}
