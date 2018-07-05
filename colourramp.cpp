#include "colourramp.h"

#include "GLEW\\glew.h"


// Assigns scaled RGB values to frame buffer on receiving corner colours.
/*
This relies on using the equation f(x, y) = a + bx + cy + dxy to fill out
the frame buffer.  Check the readme in the repository for more details.
*/
ColourRamp::ColourRamp(const std::array<unsigned short, 4> cornerVals)
    : sharedIndices{ 0, 1, 2, 2, 3, 0 }
{
    const RGB topLeft = RGB{ cornerVals[0] };
    const RGB topRight = RGB{ cornerVals[1] };
    const RGB bottomLeft = RGB{ cornerVals[2] };
    const RGB bottomRight = RGB{ cornerVals[3] };

    const RGB a = topLeft;
    const RGB b = (topRight - topLeft) / 15;
    const RGB c = (bottomLeft - topLeft) / 8;
    const RGB d = (bottomRight - bottomLeft - topRight + topLeft) / 120;

    const float widthStep = 2.0f / 16;
    const float heightStep = 2.0f / 9;
    for (short y = 0; y < 9; ++y)
    {
        // x and y need to be mapped to range [-1, 1]
        const float mappedY = 1 - (2.0f / 9) * y;
        for (short x = 0; x < 16; ++x)
        {
            Pixel& pixel = frameBuffer[y][x];
            pixel.colourVals = a + b * x + c * y + d * x * y;

            const float mappedX = (2.0f / 16) * x - 1;
            pixel.vertices[0] = { mappedX, mappedY - heightStep };
            pixel.vertices[1] = { mappedX + widthStep, mappedY - heightStep };
            pixel.vertices[2] = { mappedX + widthStep, mappedY };
            pixel.vertices[3] = { mappedX, mappedY };

            pixel.vao.Bind();
            pixel.vbo.Bind();
            pixel.vbo.Data(pixel.vertices);
            pixel.ibo.Bind();
            pixel.ibo.Data(sharedIndices);
        }
    }
}


void ColourRamp::DrawPixel(const int y, const int x, const Program& shaderProg) const
{
    const Pixel& pixel = frameBuffer[y][x];

    const float colourVals[3] = {
        pixel.colourVals.Red(),
        pixel.colourVals.Green(),
        pixel.colourVals.Blue()
    };

    shaderProg.SetUniformValue(colourVals);

    pixel.vao.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


std::ostream& operator<<(std::ostream& out, const ColourRamp& display)
{
    for (short y = 0; y < 9; ++y) {
        for (short x = 0; x < 16; ++x)
            out << display.frameBuffer[y][x].colourVals << ' ';
        out << '\n';
    }

    return out;
}
