#include <iostream>

#include <core/engine.hpp>
#include <core/maploader.hpp>
#include <render/camera.hpp>
#include <ui/text.hpp>
#include <physics/physicsObj.hpp>

#include <cstdlib>
#include <cmath>

Core::MapLoader *map;
UI::Text *text;

Render::Shaders *shader;
Render::Mesh *mesh;
Physics::PhysicsObject *meshPhys;

Render::Camera *camera;
Physics::PhysicsObject *player;

void Core::Engine::_start(){
    camera = new Render::Camera();

    map = new Core::MapLoader("resources/maps/test_map.json");
    text = new UI::Text("Brainware Engine", "resources/fonts/arial.ttf");

    shader = new Render::Shaders("resources/shaders/mesh.vert",
                            	"resources/shaders/mesh.frag");

    mesh = new Render::Mesh(Render::MESH_CUBE, shader);
    meshPhys = new Physics::PhysicsObject(Physics::COLLISION_CUBE,
        glm::vec3(1.0f),
        0.0f);
    meshPhys->rb->translate(btVector3(0.0f, 0.0f, 10.0f));

    player = new Physics::PhysicsObject(Physics::COLLISION_CUBE,
        glm::vec3(0.5f),
        10.0f);
    player->rb->translate(btVector3(0.0f, 10.0f, 10.0f));
    
    text->pos = glm::vec2(250.0f, 550.0f);
    input->cursorLock();
}

void Core::Engine::_process(float deltaTime){
    map->draw();
    mesh->draw();
    text->draw();

    btTransform transform = meshPhys->rb->getWorldTransform();
    mesh->pos = glm::vec3(transform.getOrigin().getX(),
                          transform.getOrigin().getY(),
                          transform.getOrigin().getZ());

    transform = player->rb->getWorldTransform();
    camera->pos = glm::vec3(transform.getOrigin().getX(),
                          transform.getOrigin().getY(),
                          transform.getOrigin().getZ());

    if(input->pressed(input->KEY_W)){
        player->rb->translate(btVector3(-5.0 * deltaTime * sin(glm::radians(camera->rot.y)), 0.0f, \
            -5.0 * deltaTime * cos(glm::radians(camera->rot.y))));
    }
    
    if(input->pressed(input->KEY_S)){
        player->rb->translate(btVector3(5.0 * deltaTime * sin(glm::radians(camera->rot.y)), 0.0f, \
            5.0 * deltaTime * cos(glm::radians(camera->rot.y))));
    }
    
    if(input->pressed(input->KEY_A)){
        player->rb->translate(btVector3(-5.0 * deltaTime * cos(glm::radians(camera->rot.y)), 0.0f, \
            5.0 * deltaTime * sin(glm::radians(camera->rot.y))));
    }

    if(input->pressed(input->KEY_D)){
        player->rb->translate(btVector3(5.0 * deltaTime * cos(glm::radians(camera->rot.y)), 0.0f, \
            -5.0 * deltaTime * sin(glm::radians(camera->rot.y))));
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
        "MapLoading",
        900,
        480,
        2,
        false));
    return 0;
}