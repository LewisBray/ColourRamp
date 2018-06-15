#include "colourramp.h"

#include <iostream>


// Assigns scaled RGB values to frame buffer on receiving corner colours.
/*
This relies on using the equation f(x, y) = a + bx + cy + dxy to fill out
the frame buffer.  Check the readme in the repository for more details.
*/
ColourRamp::ColourRamp(const CornerColours& rgb565Vals)
{
    frameBuffer[0][0] = RGB{ rgb565Vals.topLeft };
    frameBuffer[0][15] = RGB{ rgb565Vals.topRight };
    frameBuffer[8][0] = RGB{ rgb565Vals.bottomLeft };
    frameBuffer[8][15] = RGB{ rgb565Vals.bottomRight };

    const RGB a = frameBuffer[0][0];
    const RGB b = (frameBuffer[0][15] - frameBuffer[0][0]) / 15.0;
    const RGB c = (frameBuffer[8][0] - frameBuffer[0][0]) / 8.0;
    const RGB d = (frameBuffer[8][15] - frameBuffer[8][0]
                   - frameBuffer[0][15] + frameBuffer[0][0]) / 120.0;

    for (int y = 0; y < 9; ++y)
        for (int x = 0; x < 16; ++x)
            frameBuffer[y][x] = a + b * x + c * y + d * x * y;
}


// Outputs RGB565 values of entire grid to console on object destruction.
ColourRamp::~ColourRamp()
{
    for (int y = 0; y < 9; ++y) {
        for (int x = 0; x < 16; ++x)
            printf("%04X ", frameBuffer[y][x].ToRGB565());
        std::cout << "\n";
    }
}
