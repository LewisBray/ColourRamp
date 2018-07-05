#pragma once

#include "GLFW\\glfw3.h"


// Abstraction of GLFW window handling.
class GLFW
{
public:
    GLFW();
    ~GLFW();

    bool WindowShouldClose() const;
    void Init();
    void PollEvents() const;
    void SwapBuffers() const;

    static void CheckIfEscPressed(GLFWwindow* window,
        int key, int scanCode, int action, int mods);

private:
    GLFWwindow* window;
};
