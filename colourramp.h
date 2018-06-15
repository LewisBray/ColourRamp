#pragma once

#include "rgb.h"


// Holds corner colours with suitable member variable names.
struct CornerColours
{
    CornerColours()
        : topLeft{ 0 }
        , topRight{ 0 }
        , bottomLeft{ 0 }
        , bottomRight{ 0 }
    {}

    explicit CornerColours(const unsigned short rgb565Vals[4])
        : topLeft{ rgb565Vals[0] }
        , topRight{ rgb565Vals[1] }
        , bottomLeft{ rgb565Vals[2] }
        , bottomRight{ rgb565Vals[3] }
    {}

    unsigned short topLeft;
    unsigned short topRight;
    unsigned short bottomLeft;
    unsigned short bottomRight;
};


// Constructs and displays a colour ramp.
class ColourRamp
{
public:
    ColourRamp(const CornerColours& rgb565Vals);
    ~ColourRamp();

private:
    RGB frameBuffer[9][16];
};
