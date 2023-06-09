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

    enum MeshType {
        MESH_CUBE,
    };

    class Mesh {

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

        void Init();
        void updateBuffers();

        void setArrayBuffer(int pos, int size, unsigned int id, std::vector<float> data);
        void setElementArrayBuffer(unsigned int id, std::vector<int> data);

        public:
        glm::vec3 pos = glm::vec3(0.0f);
        glm::vec3 rot = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);
        glm::vec3 color = glm::vec3(0.8f);

        Mesh(std::vector<float> positions,
            std::vector<int> indices,
            std::vector<float> uv,
            std::vector<float> normals,
            Render::Shaders *shader,
            Render::Texture *texture = nullptr);

        Mesh(Render::MeshType type,
            Render::Shaders *shader,
            Render::Texture *texture = nullptr);
        void draw();

    };

}
