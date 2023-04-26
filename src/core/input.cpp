#include <core/input.hpp>


Core::Input::Input(GLFWwindow *window){
    this->m_pWindow = window;
}

glm::vec2 Core::Input::mousePosition(){
    double xpos, ypos;

    glfwGetCursorPos(m_pWindow, &xpos, &ypos);

    return glm::vec2((float) xpos, (float) ypos);
}

glm::vec2 Core::Input::mouseMotion(){
    if(mousePosition() == lastMousePos)
        return glm::vec2(0.0f);
    
    glm::vec2 motion = mousePosition() - lastMousePos;
    lastMousePos = mousePosition();

    return motion;
}

glm::vec3 Core::Input::getAxis(int key1, int key2,
                                int key3, int key4
) {
    glm::vec3 direction = glm::vec3(0.0f);

    direction.z -= this->pressed(key1) ? 1.0f : 0.0f;
    direction.z += this->pressed(key2) ? 1.0f : 0.0f;

    direction.x -= this->pressed(key3) ? 1.0f : 0.0f;
    direction.x += this->pressed(key4) ? 1.0f : 0.0f;

    return direction;
}

bool Core::Input::pressed(int key) {
    return glfwGetKey(m_pWindow, key) == GLFW_PRESS;
}

void Core::Input::cursorLock(){
    glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Core::Input::cursorHide(){
    glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Core::Input::cursorShow(){
    glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}