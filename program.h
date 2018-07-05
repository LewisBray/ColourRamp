#pragma once

#include "shader.h"


// Abstraction of OpenGL programs.  Only really works for
// this project as we only care about displaying "pixels".
class Program
{
public:
    Program();
    ~Program();

    void Use() const;
    void Link() const;
    void Attach(const Shader& shader) const;
    void FindUniform(const char* const uniformName);
    void SetUniformValue(const float rgbVals[3]) const;

private:
    int uniformLocation;
    unsigned programID;
};
