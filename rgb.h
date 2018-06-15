#pragma once


// Class for manipulation of RGB565 values.
class RGB
{
public:
    RGB();
    explicit RGB(const unsigned short colour);
    explicit RGB(const double red, const double green, const double blue);

    RGB operator+(const RGB& other) const;
    RGB operator-(const RGB& other) const;
    RGB operator*(const double scalar) const;
    RGB operator/(const double divisor) const;
    RGB& operator=(const RGB& other);

    unsigned short ToRGB565() const;

private:
    double r;
    double g;
    double b;
};
