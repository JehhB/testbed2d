#ifndef TESTBED2D_H
#define TESTBED2D_H

#include <testbed2d/test.h>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <set>

#define INITIAL_WINDOW_WIDTH 1280
#define INITIAL_WINDOW_HEIGHT 720

#ifndef WINDOW_TITLE
#define WINDOW_TITLE "Testbed2D"
#endif

struct Viewport
{
    int height;
    int width;
};

class Testbed2D
{
public:
    static Testbed2D *getInstance();

    void start();

    void onDraw();
    void onWindowResize(int width, int height);

    void registerTest(Test *test);
    void removeTest(Test *test);

private:
    Testbed2D();

    static Testbed2D *INSTANCE;
    Viewport viewport;
    std::set<Test *> tests;
};

#endif