#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <render/shaders.hpp>
#include <render/texture.hpp>

#include <iostream>
#include <vector>

namespace Render {

    class Sprite2D {

        GLuint vao;
        GLuint m_posBuffer;
        GLuint m_indexBuffer;
        GLuint m_uvBuffer;
        GLuint m_norBuffer;

        std::vector<float> positions;
        std::vector<int> indices;
        std::vector<float> uv;
        std::vector<float> normals;

        glm::mat4 transMat = glm::mat4(1.0f);

        Render::Shaders *m_pShader;
        Render::Texture *m_pTexture;

        void updateBuffers();

        void setArrayBuffer(int pos, int size, unsigned int id, std::vector<float> data);
        void setElementArrayBuffer(unsigned int id, std::vector<int> data);

        public:
        glm::vec2 pos = glm::vec2(0.0f);
        float rot = 0.0f;
        glm::vec2 scale = glm::vec2(1.0f);

        Sprite2D(Render::Shaders *shader,
            Render::Texture *texture);
        void draw();

    };

}
