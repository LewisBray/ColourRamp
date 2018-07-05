#include "rgb.h"

#include <algorithm>
#include <iomanip>


// Default constructor.
/*
Needed for initialisation of RGB values in ColourRamp constructor.
*/
RGB::RGB()
    : r{ 0.0 }
    , g{ 0.0 }
    , b{ 0.0 }
{}


// Constructs struct from unsigned short holding RGB565 value.
RGB::RGB(const unsigned short colour)
    : r{ static_cast<float>(colour >> 11) }
    , g{ static_cast<float>((colour >> 5) & 0b111111) }
    , b{ static_cast<float>(colour & 0b11111) }
{}


// Defined to make operator overloading implementations easier.
RGB::RGB(const float red, const float green, const float blue)
    : r{ red }
    , g{ green }
    , b{ blue }
{}


RGB RGB::operator+(const RGB& other) const
{
    return RGB{ r + other.r, g + other.g, b + other.b };
}


RGB RGB::operator-(const RGB& other) const
{
    return RGB{ r - other.r, g - other.g, b - other.b };
}


RGB RGB::operator*(const float scalar) const
{
    return RGB{ scalar * r, scalar * g, scalar * b };
}


RGB RGB::operator/(const float divisor) const
{
    return RGB{ r / divisor, g / divisor, b / divisor };
}


RGB& RGB::operator=(const RGB& other)
{
    r = other.r;
    g = other.g;
    b = other.b;

    return *this;
}


// Getter functions that normalise the RGB vals to the range [0, 1]
float RGB::Red() const
{
    return r / 31;
}


float RGB::Green() const
{
    return g / 63;
}


float RGB::Blue() const
{
    return b / 31;
}


// Outputs the RGB struct as its unsigned short RGB565 value.
std::ostream& operator<<(std::ostream& out, const RGB& rgbVals)
{
    const unsigned short red = static_cast<unsigned short>(std::round(rgbVals.r));
    const unsigned short green = static_cast<unsigned short>(std::round(rgbVals.g));
    const unsigned short blue = static_cast<unsigned short>(std::round(rgbVals.b));

    const unsigned short rgb565 = (red << 11) + (green << 5) + blue;

    out << std::setfill('0') << std::setw(4)
        << std::uppercase << std::hex << rgb565;

    return out;
}
