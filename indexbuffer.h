#pragma once


// Abstraction of OpenGL index buffer objects.
class IndexBuffer
{
public:
    IndexBuffer();
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;
    void Data(const unsigned indices[]) const;

private:
    unsigned iboID;
};
