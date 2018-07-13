#version 330 core

in vec2 v2pos;

void main()
{
    mat4 transform = mat4(
        2.0 / 16.0,        0.0, 0.0,  0.0,
               0.0, -2.0 / 9.0, 0.0,  0.0,
               0.0,        0.0, 1.0,  0.0,
              -1.0,        1.0, 0.0,  1.0
    );

    vec4 position = vec4(v2pos, 1.0, 1.0);

    gl_Position = transform * position;
}