#include "colour_ramp.h"
#include "input_check.h"
#include "rendering.h"

#include "colour_ramp.cpp"
#include "input_check.cpp"
#include "rendering.cpp"

#define GLEW_STATIC
#include "glew/glew.h"
#include "glfw/glfw3.h"

static GLuint construct_shader(const GLenum type, const char* const filepath) {
    FILE* input_file = std::fopen(filepath, "r");

    std::fseek(input_file, 0, SEEK_END);
    const GLint file_size = std::ftell(input_file);
    std::rewind(input_file);

    void* const buffer = std::malloc(file_size);
    std::fread(buffer, 1, file_size, input_file);

    const GLuint shader = glCreateShader(type);
    const char* const shader_source = static_cast<const char*>(buffer);
    glShaderSource(shader, 1, &shader_source, &file_size);
    glCompileShader(shader);

    std::free(buffer);

    return shader;
}

int main(const int argc, const char* argv[]) {
    const ParseUserInputResult parse_user_input_result = parse_user_input(argc, argv);
    if (parse_user_input_result.error != nullptr) {
        std::puts(parse_user_input_result.error);
        return -1;
    }

    if (glfwInit() == GLFW_FALSE) {
        std::puts("Failed to initialise GLFW.");
        return -1;
    }

    GLFWwindow* const window = glfwCreateWindow(800, 450, "Colour Ramp", nullptr, nullptr);
    if (window == nullptr) {
        std::puts("Failed to create window.");
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::puts("Error intialising GLEW.");
        return -1;
    }

    const ColourRamp colour_ramp = construct_colour_ramp(parse_user_input_result.corner_colours);
    print_rgb565_values_to_console(colour_ramp);

    const Vertices vertices = construct_vertices_for_colour_ramp(colour_ramp);

    GLuint vertex_buffer = 0;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices.buffer), static_cast<const void*>(vertices.buffer), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(sizeof(Vec2)));

    const Indices indices = construct_indices_for_colour_ramp();

    GLuint index_buffer = 0;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices.buffer), static_cast<const void*>(indices.buffer), GL_STATIC_DRAW);

    const GLuint shader_program = glCreateProgram();

    const GLuint vertex_shader = construct_shader(GL_VERTEX_SHADER, "./shaders/vertex.shader");
    const GLuint fragment_shader = construct_shader(GL_FRAGMENT_SHADER, "./shaders/fragment.shader");

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glUseProgram(shader_program);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6 * COLOUR_RAMP_TILE_COUNT, GL_UNSIGNED_SHORT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
