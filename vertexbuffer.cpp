#include "vertexbuffer.h"

#include "GLEW\\glew.h"


VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &vboID);
}


VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &vboID);
}


void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
}


void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void VertexBuffer::Data(const Vertex vertices[]) const
{
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
}
