#include <iostream>
#include <core/engine.hpp>
#include <render/camera.hpp>
#include <render/text.hpp>

//Render::Camera *camera;
Render::Text *text;

void Core::Engine::_start(){
    //camera = new Render::Camera();
    text = new Render::Text("Hello!", "resources/fonts/arial.ttf");
}

void Core::Engine::_process(float deltaTime){
    text->draw();
}

void Core::Engine::_input(int key){

}

void Core::Engine::_exit_window(){
    
}

auto main() -> int {
    Core::Engine engine(Core::Config(
        "Text",
        900,
        480,
        2,
        false));
    return 0;
}
