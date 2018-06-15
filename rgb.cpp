#include "rgb.h"

#include <algorithm>


// Default constructor.
/*
Needed for initialisation of RGB values in ColourRamp constructor.
*/
RGB::RGB()
    : r{ 0.0 }
    , g{ 0.0 }
    , b{ 0.0 }
{}


// Constructs class from unsigned short holding RGB565 value.
RGB::RGB(const unsigned short colour)
    : r{ static_cast<double>(colour >> 11) }
    , g{ static_cast<double>((colour >> 5) & 0b111111) }
    , b{ static_cast<double>(colour & 0b11111) }
{}


// Defined to make operator overloading implementations easier.
RGB::RGB(const double red, const double green, const double blue)
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


RGB RGB::operator*(const double scalar) const
{
    return RGB{ scalar * r, scalar * g, scalar * b };
}


RGB RGB::operator/(const double divisor) const
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


// Converts the member variables back to a single RGB565 value.
unsigned short RGB::ToRGB565() const
{
    const unsigned short red = static_cast<unsigned short>(std::round(r));
    const unsigned short green = static_cast<unsigned short>(std::round(g));
    const unsigned short blue = static_cast<unsigned short>(std::round(b));

    return (red << 11) + (green << 5) + blue;
}
