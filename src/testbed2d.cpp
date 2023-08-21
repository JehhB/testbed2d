#include <testbed2d/testbed2d.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <iostream>

static void createUI(GLFWwindow *window);
static void destroyUI();
static void errorCallback(int error, const char *description);
static void framebufferSizeCallback(GLFWwindow *window, int width, int height);

Testbed2D *Testbed2D::INSTANCE = nullptr;
Testbed2D *Testbed2D::getInstance()
{
    if (INSTANCE == nullptr)
    {
        INSTANCE = new Testbed2D();
    }
    return INSTANCE;
}

Testbed2D::Testbed2D()
{
    viewport.width = INITIAL_WINDOW_WIDTH;
    viewport.height = INITIAL_WINDOW_HEIGHT;
}

void Testbed2D::start()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW Init failed" << std::endl;
        assert(false);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(
        viewport.width,
        viewport.height,
        WINDOW_TITLE,
        NULL,
        NULL);
    if (!window)
    {
        std::cerr << "GLFW Create window failed" << std::endl;
        glfwTerminate();
        assert(false);
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "GLAD Faild to load OpenGL loader" << std::endl;
        glfwTerminate();
        assert(false);
    }

    glfwSetErrorCallback(errorCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        framebufferSizeCallback(window, width, height);
    }

    createUI(window);

    while (!glfwWindowShouldClose(window))
    {
        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        onDraw();
        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This is a simple ImGui window.");
        ImGui::End();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    destroyUI();
    glfwTerminate();
}

void Testbed2D::onDraw()
{
    ImGui::Begin("Hello, ImGui!");
    ImGui::Text("This is a simple ImGui window.");
    ImGui::End();

    glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Testbed2D::onWindowResize(int width, int height)
{
    viewport.width = width;
    viewport.height = height;
    glViewport(0, 0, width, height);
}

static void createUI(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    if (!ImGui_ImplGlfw_InitForOpenGL(window, true))
    {
        std::cerr << "IMGUI Init for opengl failed" << std::endl;
        assert(false);
    }

    if (!ImGui_ImplOpenGL3_Init("#version 330"))
    {
        std::cerr << "IMGUI Init failed" << std::endl;
        assert(false);
    }
}

static void destroyUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

static void errorCallback(int error, const char *description)
{
    std::cerr << "GLFW ERROR: " << description << std::endl;
}

static void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    Testbed2D::getInstance()->onWindowResize(width, height);
}