#include "Core/Application.h"



namespace Rendering
{
    Application* Application::instance = nullptr;

    Application::Application(void)
    {
        ///Window Initiation
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        ///Create a windowed mode window and its OpenGL context
        GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
        }

        ///Make the window's context current
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        ///Load Open Gl function
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }

        ///Clear the color of the screen in blue
        glClearColor(0, 0, 0, 1.0f);

        this->screen = window;
        this->width = 800;
        this->height = 600;
        this->MainCamera = nullptr;

        Application::instance = this;
    }

    Application::Application(int width, int height)
    {
        this->width = width;
        this->height = height;

        ///Window Initiation
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        ///Create a windowed mode window and its OpenGL context
        GLFWwindow* window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
        }

        ///Make the window's context current
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        ///Load Open Gl function
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }

        ///Clear the color of the screen in blue
        glClearColor(0, 0, 0, 1.0f);

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        this->screen = window;
        this->MainCamera = nullptr;
        Application::instance = this;
    }

    void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void Application::mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        Application::instance->MainCamera->CameraInputHandler(xpos, ypos);
    }

    float Application::getDeltaTime()
    {
        return this->deltaTime;
    }

    void Application::updateDeltaTime()
    {
        ///Calculate the Delta Time
        float currentFrame = glfwGetTime();
        this->deltaTime = currentFrame - lastFrame;
        this->lastFrame = currentFrame;
    }

    void Application::processInput(GLFWwindow* window)
    {
        ///Quit the window when you press ESCAPE
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
}

