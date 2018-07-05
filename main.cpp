#include "colourramp.h"
#include "inputcheck.h"
#include "GLEW\\glew.h"
#include "glfwclass.h"
#include "program.h"
#include "error.h"


int main(int argc, char* argv[])
{
    GLFW glfw;
    std::array<unsigned short, 4> inputVals;
    try {
        glfw.Init();
        inputVals = ParseInputs(argc, argv);
    }
    catch (const Error& error) {
        std::cout << error.message << '\n';
        return -1;
    }
    
    if (glewInit() != GLEW_OK) {
        std::cout << "Error intialising GLEW!\n\n";
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << "\n\n";

    ColourRamp colourRamp{ inputVals };

    std::cout << colourRamp << '\n';


    Program shaderProg;

    const Shader vertShader{ GL_VERTEX_SHADER, "Shaders\\vertex.shader" };
    const Shader fragShader{ GL_FRAGMENT_SHADER, "Shaders\\fragment.shader" };

    shaderProg.Attach(vertShader);
    shaderProg.Attach(fragShader);
    shaderProg.Link();

    shaderProg.Use();
    shaderProg.FindUniform("u_colour");

    while (!glfw.WindowShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        for (int y = 0; y < 9; ++y)
            for (int x = 0; x < 16; ++x)
                colourRamp.DrawPixel(y, x, shaderProg);

        glfw.SwapBuffers();
        glfw.PollEvents();
    }

    return 0;
}
