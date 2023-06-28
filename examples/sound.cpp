#include <iostream>
#include <core/engine.hpp>
#include <core/sound.hpp>
#include <render/camera.hpp>
#include <cstdlib>

Render::Camera *camera;

void Core::Engine::_start(){
    camera = new Render::Camera();
    ISoundEngine *sound_engine = createIrrKlangDevice();
    ISound* music = sound_engine->play3D("resources/sounds/test.wav",
                        vec3df(0,0,0), true, false, true);

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
        "Sound",
        900,
        480,
        2,
        false));
    return 0;
}