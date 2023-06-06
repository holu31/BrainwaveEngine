#include <render/texture.hpp>
#include <core/engine.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Render::Texture::Texture(std::string texturePath){
    int width, height, nrChannels;

    LOG(data = stbi_load(texturePath.c_str(), &width,
        &height, &nrChannels, 4), "INFO", "stbi loading texture");

    LOG(glGenTextures(1, &id), "INFO", "generating texture; from image -> opengl");  
    size = glm::ivec2(width, height);
    channels = nrChannels;
}

void Render::Texture::import() {
    this->bind();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D,
        0, GL_RGBA,
        size.x, size.y,
        0, GL_RGBA,
        GL_UNSIGNED_BYTE, data);

    this->unbind();

    LOG(stbi_image_free(data), "INFO", "free image from memory");
}

void Render::Texture::bind(){
    glBindTexture(GL_TEXTURE_2D, id);
}
void Render::Texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, GL_FALSE);
}