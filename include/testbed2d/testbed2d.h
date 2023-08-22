#ifndef TESTBED2D_H
#define TESTBED2D_H

#include <testbed2d/test.h>
#include <testbed2d/draw.h>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <set>

#ifndef WINDOW_TITLE
#define WINDOW_TITLE "Testbed2D"
#endif

class Testbed2D
{
public:
    static Testbed2D *getInstance();
    static void destoyInstance(Testbed2D *instance);

    void start();

    void onDraw();
    void onDrawMenuBar();

    void onWindowResize(int width, int height);

    void registerTest(Test *test);
    void removeTest(Test *test);

private:
    Testbed2D();
    ~Testbed2D();

    static Testbed2D *INSTANCE;
    Viewport viewport;
    std::set<Test *> tests;
    DebugDraw debugDraw;
};

#endif