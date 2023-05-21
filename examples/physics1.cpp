#include <iostream>
#include <core/engine.hpp>
#include <render/camera.hpp>
#include <physics/physicsObj.hpp>
#include <cstdlib>
#include <cmath>

Render::Mesh *mesh;
Render::Camera *camera;
Render::Shaders *shader;
Render::Texture *texture;
Physics::PhysicsObject *meshPhys;

void Core::Engine::_start(){
    shader = new Render::Shaders("resources/shaders/mesh.vert",
                            	"resources/shaders/mesh.frag");
    texture = new Render::Texture("resources/cringe.jpg");
    camera = new Render::Camera();
    mesh = new Render::Mesh(Render::MESH_CUBE, shader, texture=texture);
    meshPhys = new Physics::PhysicsObject(Physics::COLLISION_CUBE,
        glm::vec3(1.0f),
        10.0f);

    camera->pos = glm::vec3(0.0f, 0.0f, 3.0f);
}

void Core::Engine::_process(float deltaTime){
    mesh->draw();
    btTransform transform = meshPhys->rb->getWorldTransform();
    mesh->pos = glm::vec3(transform.getOrigin().getX(),
                          transform.getOrigin().getY(),
                          transform.getOrigin().getZ());
}

void Core::Engine::_input(int key){
    std::cout << key << std::endl;
}

void Core::Engine::_exit_window(){
    
}

auto main() -> int {
    Core::Engine engine(Core::Config(
        "Physics1",
        900,
        480,
        2,
        false));
    return 0;
}
