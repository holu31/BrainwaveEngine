#include <iostream>
#include <core/engine.hpp>
#include <render/camera.hpp>
#include <render/light.hpp>
#include <render/texture.hpp>
#include <cstdlib>

Render::Mesh *mesh;
Render::Mesh *mesh2;
Render::Camera *camera;
Render::DirectionalLight *dlight;
Render::Shaders *shader;
Render::Texture *texture;

void Core::Engine::_start(){
    shader = new Render::Shaders("resources/shaders/mesh.vert",
                            	"resources/shaders/mesh.frag");
    texture = new Render::Texture("resources/cringe.jpg");
    camera = new Render::Camera();
    dlight = new Render::DirectionalLight();
    dlight->pos = glm::vec3(-2.0f, 0.0f, 3.0f);
    mesh = new Render::Mesh(Render::MESH_CUBE, shader);
    mesh2 = new Render::Mesh(Render::MESH_CUBE, shader);
    mesh2->pos.x = 2.0f;

    camera->pos = glm::vec3(0.0f, 0.0f, 3.0f);
    input->cursorLock();
}

void Core::Engine::_process(float deltaTime){
    mesh->draw();
    mesh2->draw();
    //mesh->rot += glm::vec3(12.0f, 12.0f, 0.0f) * deltaTime;

    if(input->pressed(input->KEY_W)){
        camera->pos.x += -5.0 * deltaTime * sin(glm::radians(camera->rot.y));
        camera->pos.z += -5.0 * deltaTime * cos(glm::radians(camera->rot.y));
    }
    
    if(input->pressed(input->KEY_S)){
        camera->pos.x += 5.0 * deltaTime * sin(glm::radians(camera->rot.y));
        camera->pos.z += 5.0 * deltaTime * cos(glm::radians(camera->rot.y));
    }
    
    if(input->pressed(input->KEY_A)){
        camera->pos.x += -5.0 * deltaTime * cos(glm::radians(camera->rot.y));
        camera->pos.z += 5.0 * deltaTime * sin(glm::radians(camera->rot.y));
    }

    if(input->pressed(input->KEY_D)){
        camera->pos.x += 5.0 * deltaTime * cos(glm::radians(camera->rot.y));
        camera->pos.z += -5.0 * deltaTime * sin(glm::radians(camera->rot.y));
    }

    if(input->pressed(input->KEY_ESCAPE)) input->cursorShow();

    glm::vec2 motion = input->mouseMotion();
    camera->rot.y -= motion.x * .1f;
    camera->rot.x -= motion.y * .1f;
}

void Core::Engine::_input(int key){
    std::cout << key << std::endl;
}

void Core::Engine::_exit_window(){

}

auto main() -> int {
    Core::Engine engine(Core::Config(
        "Light",
        900,
        480,
        2,
        false));
    return 0;
}
