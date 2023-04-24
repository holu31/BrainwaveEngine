#include <core/engine.hpp>

#include <linmath.h>

#include <stdexcept>

Core::Engine::~Engine()
{
    std::cout << "destroyed window\n";
    this->_exit_window();

    glfwDestroyWindow(this->m_window);
    glfwTerminate();
}

void frameBufferSizeCallback(GLFWwindow *window, 
    int width, int height)
{
    glViewport(0, 0, width, height);
}

Core::Engine::Engine(std::string title, 
    int width, int height)
{

    glfwInit();

    m_prevDeltaTime = (float) glfwGetTime();

    glfwDefaultWindowHints();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_window) throw std::runtime_error("failed to create window");

    glfwMakeContextCurrent(this->m_window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        throw std::runtime_error("glad run failed");
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    
    glClearColor(0.4f, 0.4f, 0.4f, 0.0f);

    glfwSetFramebufferSizeCallback(m_window, frameBufferSizeCallback);

    //glfwSetKeyCallback(m_window, input);
    
    this->_start();

    while(!glfwWindowShouldClose(this->m_window)) {

        glfwPollEvents(); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float deltaTime = (float) glfwGetTime() - m_prevDeltaTime;
		m_prevDeltaTime = (float) glfwGetTime();

        this->_process(deltaTime * 150.0f);

        glfwSwapBuffers(m_window);
        glFinish();
    }
}
