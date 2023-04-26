#include <iostream>
#include <core/engine.hpp>
#include <render/camera.hpp>
#include <cstdlib>

Render::Mesh *mesh;
Render::Camera *camera;
Render::Shaders *shader;
Render::Texture *texture;

void Core::Engine::_start(){
    shader = new Render::Shaders("resources/shaders/mesh.vert",
                            	"resources/shaders/mesh.frag");
    texture = new Render::Texture("resources/cringe.jpg");
    camera = new Render::Camera();
    mesh = new Render::Mesh(Render::MESH_CUBE, shader, texture=texture);
    camera->pos.z += 5.0f;
    camera->pos.y += 2.0f;

    input->cursorLock();
}

void Core::Engine::_process(float deltaTime){
    mesh->draw();

    if(input->pressed(Input::KEY_ESCAPE)) input->cursorShow();

    glm::vec3 dir = input->getAxis(
        Input::KEY_W,
        Input::KEY_S,
        Input::KEY_A,
        Input::KEY_D
    );

    camera->pos += dir * 2.5f * deltaTime;

    auto motion = input->mouseMotion();
    
    camera->rot.y -= motion.x * .1f;
    camera->rot.x -= motion.y * .1f;
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
