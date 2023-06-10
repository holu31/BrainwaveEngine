#include <core/engine.hpp>

#include <linmath.h>

#include <stdexcept>

Core::Engine::~Engine()
{
    LOG(this->_exit_window(), "INFO", "destroyed window");

    glfwDestroyWindow(this->m_window);
    glfwTerminate();
}

void frameBufferSizeCallback(GLFWwindow *window, 
    int width, int height)
{
    glViewport(0, 0, width, height);
}

Core::Engine::Engine(Core::Config config)
{

    LOG(glfwInit(), "INFO", "initializate glfw");

    m_prevDeltaTime = (float) glfwGetTime();

    glfwDefaultWindowHints();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    if (!config.m_resizable)
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_SAMPLES, config.m_msaa);

    LOG(this->m_window = glfwCreateWindow(config.m_width, config.m_height,
                            config.m_title.c_str(), nullptr, nullptr), "INFO", \
                            "creating window");
    if (!m_window) throw LOG(!m_window, "ERROR", "failed to create window");

    glfwMakeContextCurrent(this->m_window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        throw LOG(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "ERROR", \
            "glad run failed");
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glClearColor(0.4f, 0.4f, 0.4f, 0.0f);

    glfwSetFramebufferSizeCallback(m_window, frameBufferSizeCallback);

    input = new Core::Input(m_window);
    physics = new Physics::Physics();

    //glfwSetKeyCallback(m_window, input);
    
    this->_start();

    if(!config.m_vsync) glfwSwapInterval(0);

    while(!glfwWindowShouldClose(this->m_window)) {

        glfwPollEvents(); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float deltaTime = (float) glfwGetTime() - m_prevDeltaTime;
		m_prevDeltaTime = (float) glfwGetTime();

        Physics::Physics::dynamicsWorld->stepSimulation(deltaTime, 7);

        this->_process(deltaTime);

        glfwSwapBuffers(m_window);
    }
}
