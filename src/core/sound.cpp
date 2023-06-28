#include <core/sound.hpp>
#include <core/engine.hpp>


Core::Sound::Sound(std::string path){
    this->m_pPath = path;
    sound_engine = createIrrKlangDevice();

    if (!this->sound_engine)
        throw LOG(!this->sound_engine, "ERROR", "sound engine run failed.");

    this->music = sound_engine->play3D(path.c_str(),
                                  vec3df(0,0,0), true, false, true);
}

void Core::Sound::update(){
    music->setPosition(vec3df(this->pos.x, this->pos.y, this->pos.z));
}