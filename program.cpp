#include "program.h"

#include "GLEW\\glew.h"


Program::Program()
{
    programID = glCreateProgram();
}


Program::~Program()
{
    glDeleteProgram(programID);
}


void Program::Use() const
{
    glUseProgram(programID);
}


void Program::Link() const
{
    glLinkProgram(programID);
    glValidateProgram(programID);
}


void Program::Attach(const Shader& shader) const
{
    glAttachShader(programID, shader.GetID());
}


void Program::FindUniform(const char* const name)
{
    uniformLocation = glGetUniformLocation(programID, name);
}


void Program::SetUniformValue(const float rgbVals[3]) const
{
    glUniform3f(uniformLocation, rgbVals[0], rgbVals[1], rgbVals[2]);
}
