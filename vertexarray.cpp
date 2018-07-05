#include "vertexarray.h"

#include "GLEW\\glew.h"


VertexArray::VertexArray()
{
    glGenVertexArrays(1, &vaoID);
}


VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &vaoID);
}


void VertexArray::Bind() const
{
    glBindVertexArray(vaoID);
}


void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}
