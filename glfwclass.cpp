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

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    window = glfwCreateWindow(mode->width,
        mode->height, "Colour Ramp", monitor, NULL);
    if (window == nullptr) {
        glfwTerminate();
        throw Error{ "Failed to create window.\n\n" };
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, CheckIfEscPressed);
}


void GLFW::PollEvents() const
{
    glfwPollEvents();
}


void GLFW::SwapBuffers() const
{
    glfwSwapBuffers(window);
}


void GLFW::CheckIfEscPressed(GLFWwindow* window,
    int key, int scanCode, int action, int mods)
{
    if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
        glfwSetWindowShouldClose(window, GL_TRUE);
}
