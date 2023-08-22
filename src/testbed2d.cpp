#include <testbed2d/testbed2d.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <iostream>

static void createUI(GLFWwindow *window);
static void destroyUI();
static void errorCallback(int error, const char *description);
static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
static void listTests(std::set<Test *> &tests);

Testbed2D *Testbed2D::INSTANCE = nullptr;
Testbed2D *Testbed2D::getInstance()
{
    if (INSTANCE == nullptr)
    {
        INSTANCE = new Testbed2D();
    }
    return INSTANCE;
}

void Testbed2D::destoyInstance(Testbed2D *instance)
{
    delete instance;
}

Testbed2D::Testbed2D()
{
    debugDraw.viewport = &viewport;
}

Testbed2D::~Testbed2D()
{
    debugDraw.Destroy();
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
    debugDraw.Create();

    while (!glfwWindowShouldClose(window))
    {
        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This is a simple ImGui window.");
        ImGui::End();

        onDrawMenuBar();
        onDraw();
        debugDraw.Flush();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    destroyUI();
    glfwTerminate();
}

void Testbed2D::onDrawMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Tests"))
        {
            listTests(tests);
            ImGui::EndMenu();
        }
        // Add more menu items here...

        ImGui::EndMainMenuBar();
    }
}

void Testbed2D::onDraw()
{
    b2Color color{1.0f, 0.0f, 0.0f};
    b2Vec2 center{0, 0};
    debugDraw.DrawCircle(center, 1.0f, color);
    b2Vec2 start{-1, -1};
    b2Vec2 end{1, 1};
    debugDraw.DrawSegment(start, end, color);
}

void Testbed2D::onWindowResize(int width, int height)
{
    viewport.width = width;
    viewport.height = height;
    glViewport(0, 0, width, height);
}

void Testbed2D::registerTest(Test *test)
{
    tests.insert(test);
}

void Testbed2D::removeTest(Test *test)
{
    tests.erase(test);
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

static void listTests(std::set<Test *> &tests)
{
    if (tests.size() == 0)
    {
        ImGui::TextDisabled("No test registered");
        return;
    }

    for (Test *test : tests)
    {
        if (ImGui::MenuItem(test->getTestName(), NULL, nullptr))
        {
            // TODO: switch test
        }
    }
}