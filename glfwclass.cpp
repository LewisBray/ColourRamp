#include "glfwclass.h"
#include "error.h"


GLFW::GLFW()
    : window{ nullptr }
{}


GLFW::~GLFW()
{
    glfwTerminate();
}


bool GLFW::WindowShouldClose() const
{
    return glfwWindowShouldClose(window);
}


void GLFW::Init()
{
    if (!glfwInit())
        throw Error{ "Failed to initialise GLFW.\n\n" };

    window = glfwCreateWindow(640, 480, "Colour Ramp", NULL, NULL);
    if (window == nullptr) {
        glfwTerminate();
        throw Error{ "Failed to create window.\n\n" };
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}


void GLFW::PollEvents() const
{
    glfwPollEvents();
}


void GLFW::SwapBuffers() const
{
    glfwSwapBuffers(window);
}
