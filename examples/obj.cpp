#include <iostream>

#include <core/engine.hpp>
#include <render/camera.hpp>
#include <render/obj.hpp>

#include <cstdlib>

Render::Mesh *mesh;
Render::Camera *camera;
Render::Shaders *shader;
Render::ObjLoader *obj;

void Core::Engine::_start(){
    shader = new Render::Shaders("resources/shaders/mesh.vert",
                            	"resources/shaders/mesh.frag");
    camera = new Render::Camera();
    obj = new Render::ObjLoader("resources/models/test.bwm");
    mesh = new Render::Mesh(obj->positions,
        obj->indices,
        obj->colors,
        obj->uv,
        shader);

    camera->pos = glm::vec3(0.0f, 0.0f, 3.0f);
}

void Core::Engine::_process(float deltaTime){
    mesh->draw();

    mesh->rot += glm::vec3(12.0f, 12.0f, 0.0f) * deltaTime;
}

void Core::Engine::_input(int key){
    std::cout << key << std::endl;
}

void Core::Engine::_exit_window(){
    
}

auto main() -> int {
    Core::Engine engine(Core::Config(
        "Cube",
        900,
        480,
        2,
        false));
    return 0;
}
