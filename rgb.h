#pragma once

#include <iostream>


// Class for manipulation of RGB565 values.
struct RGB
{
public:
    RGB();
    explicit RGB(const unsigned short colour);
    RGB(const float red, const float green, const float blue);

    RGB operator+(const RGB& other) const;
    RGB operator-(const RGB& other) const;
    RGB operator*(const float scalar) const;
    RGB operator/(const float divisor) const;
    RGB& operator=(const RGB& other);

    float Red() const;
    float Green() const;
    float Blue() const;

    friend std::ostream& operator<<(std::ostream& out, const RGB& rgbVals);

private:
    float r;
    float g;
    float b;
};
