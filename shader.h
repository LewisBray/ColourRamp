#pragma once

#include <string>


// Abstraction of OpenGL shaders.
class Shader
{
public:
    Shader(const unsigned type, const std::string& filepath);
    ~Shader();

    unsigned GetID() const;

private:
    unsigned shaderID;
};
