#include <iostream>
#include <core/engine.hpp>
#include <render/camera.hpp>
#include <render/sprite2d.hpp>
#include <render/texture.hpp>
#include <cstdlib>

Render::Sprite2D *sprite;
Render::Camera *camera;
Render::Shaders *shader;
Render::Texture *texture;

void Core::Engine::_start(){
    shader = new Render::Shaders("resources/shaders/sprite.vert",
                            	"resources/shaders/sprite.frag");
    texture = new Render::Texture("resources/test.png");
    camera = new Render::Camera();
    sprite = new Render::Sprite2D(shader, texture);
    sprite->scale = glm::vec2(0.5f, 0.3f);

    camera->pos = glm::vec3(0.0f, 0.0f, 20.0f);
}

void Core::Engine::_process(float deltaTime){
    sprite->draw();
}

void Core::Engine::_input(int key){
    std::cout << key << std::endl;
}

void Core::Engine::_exit_window(){

}

auto main() -> int {
    Core::Engine engine(Core::Config(
        "Sprite2D",
        900,
        480,
        2,
        false));
    return 0;
}