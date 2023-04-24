#include <render/camera.hpp>

Core::Camera::Camera() {
    if (current == nullptr)
        current = this;
}

glm::mat4 Core::Camera::projMatGet(){
    glm::mat4 projMat = glm::mat4(1.0f);
    projMat = glm::perspective(glm::radians(fov), 960.0f / 540.0f, near, far);

    return projMat;
}

glm::mat4 Core::Camera::viewMatGet(){
    glm::mat4 viewMat = glm::mat4(1.0f);
    
    viewMat = glm::rotate(viewMat, glm::radians(-rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
    viewMat = glm::rotate(viewMat, glm::radians(-rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
    viewMat = glm::rotate(viewMat, glm::radians(-rot.z), glm::vec3(0.0f, 0.0f, 1.0f));

    viewMat = glm::translate(viewMat, -pos);
    viewMat = glm::scale(viewMat, scale);

    return viewMat;
}

Core::Camera* Core::Camera::current = nullptr;
