#include "shader.h"
#include "error.h"

#include "GLEW\\glew.h"

#include <sstream>
#include <fstream>
#include <memory>


Shader::Shader(const unsigned type, const std::string& filepath)
{
    std::ifstream inputFile{ filepath };

    std::stringstream fileContents;
    fileContents << inputFile.rdbuf();

    const std::string shaderSrcStr = fileContents.str();
    const char* const shaderSrc = shaderSrcStr.c_str();

    shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &shaderSrc, NULL);
    glCompileShader(shaderID);
}


Shader::~Shader()
{
    glDeleteShader(shaderID);
}


unsigned Shader::GetID() const
{
    return shaderID;
}
