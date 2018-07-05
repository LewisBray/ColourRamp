#pragma once


// Used for working with 2D position vertices.
struct Vertex
{
    float x;
    float y;
};


// Abstraction of OpenGL vertex buffer arrays.
class VertexBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
    void Data(const Vertex vertices[]) const;

private:
    unsigned vboID;
};
