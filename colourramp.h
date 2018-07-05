#pragma once

#include "rgb.h"
#include "program.h"
#include "vertexarray.h"
#include "indexbuffer.h"
#include "vertexbuffer.h"

#include <array>


// Everything needed for drawing a pixel on the screen.
struct Pixel
{
    RGB colourVals;
    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ibo;
    Vertex vertices[4];
};


// Constructs and displays a colour ramp.
class ColourRamp
{
public:
    explicit ColourRamp(const std::array<unsigned short, 4> cornerVals);

    void DrawPixel(const int row, const int col, const Program& shaderProg) const;

    friend std::ostream& operator<<(std::ostream& out, const ColourRamp& display);

private:
    Pixel frameBuffer[9][16];
    const unsigned sharedIndices[6];    // All pixels use same index buffer
};
