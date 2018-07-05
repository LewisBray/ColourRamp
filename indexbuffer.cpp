#include "indexbuffer.h"

#include "GLEW\\glew.h"


IndexBuffer::IndexBuffer()
{
    glGenBuffers(1, &iboID);
}


IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &iboID);
}


void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
}


void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


// This only works if we have six indices.
void IndexBuffer::Data(const unsigned indices[]) const
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        6 * sizeof(unsigned), indices, GL_STATIC_DRAW);
}
