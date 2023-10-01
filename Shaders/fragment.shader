#version 330 core

in vec3 frag_colour;

out vec4 o_colour;

void main() {
    o_colour = vec4(frag_colour, 1.0);
}
