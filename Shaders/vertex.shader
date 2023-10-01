#version 330 core

layout (location = 0) in vec2 a_position;
layout (location = 1) in vec3 a_colour;

out vec3 frag_colour;

void main() {
    mat2 scaling = mat2(
        2.0 / 16.0,        0.0,
               0.0, -2.0 / 9.0
    );

    vec2 translation = vec2(-1.0, 1.0);

    vec2 position = scaling * a_position + translation;

    gl_Position = vec4(position, 0.0, 1.0);
    frag_colour = a_colour;
}
