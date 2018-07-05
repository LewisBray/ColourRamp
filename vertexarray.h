#pragma once


// Abstraction of OpenGL vertex array objects.
class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

private:
    unsigned vaoID;
};
