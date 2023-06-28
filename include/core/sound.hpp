#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <IrrKlang/irrKlang.h>
#include <iostream>

using namespace irrklang;

namespace Core {

    class Sound {

        ISoundEngine* sound_engine;
        ISound* music;
        std::string m_pPath;

    public:

        glm::vec3 pos = glm::vec3(0.0f);

        Sound(std::string path);
        void update();

    };

}