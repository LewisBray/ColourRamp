#version 330 core

out vec4 outputColour;

uniform vec3 u_colour;

void main()
{
    outputColour = vec4(u_colour, 1.0);
}