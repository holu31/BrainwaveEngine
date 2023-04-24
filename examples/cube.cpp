#include <iostream>
#include <core/engine.hpp>
#include <render/camera.hpp>

Core::Shaders *shader;
Core::Mesh *mesh;
Core::Camera *camera;

void Core::Engine::_start(){
    shader = new Core::Shaders("assets/shaders/mesh.vert",
                                "assets/shaders/mesh.frag");
    camera = new Core::Camera();
    mesh = new Core::Mesh(MESH_CUBE, shader);
    camera->pos.z += 5.0f;
    camera->pos.y += 2.0f;
}

void Core::Engine::_process(float deltaTime){
    mesh->draw();
    mesh->rot.x -= 0.5f * deltaTime;
}

void Core::Engine::_input(int key){
    std::cout << key << std::endl;
}

void Core::Engine::_exit_window(){
    
}

auto main() -> int {
    Core::Engine engine("test", 900, 480);
    return 0;
}
