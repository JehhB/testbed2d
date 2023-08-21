#ifndef TESTBED2D_H
#define TESTBED2D_H

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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

private:
    Testbed2D();

    static Testbed2D *INSTANCE;
    Viewport viewport;
};

#endif