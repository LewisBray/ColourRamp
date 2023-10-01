#include "colour_ramp.h"

static RGB construct_rgb_from_rgb565(const RGB565 rgb565) {
    const float r = static_cast<float>(rgb565 >> 11) / 31.0f;
    const float g = static_cast<float>((rgb565 >> 5) & 0x3F) / 63.0f;
    const float b = static_cast<float>(rgb565 & 0x1F) / 31.0f;
    return RGB{ r, g, b };
}

static RGB565 construct_rgb565_from_rgb(const RGB& rgb) {
    // only dealing with non-negative colour values so this rouding style is fine
    const unsigned short r = static_cast<unsigned short>(31.0f * rgb.r + 0.5f);
    const unsigned short g = static_cast<unsigned short>(63.0f * rgb.g + 0.5f);
    const unsigned short b = static_cast<unsigned short>(31.0f * rgb.b + 0.5f);

    return (r << 11) + (g << 5) + b;
}

static RGB operator+(const RGB& lhs, const RGB& rhs) {
    return RGB{ lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b };
}

static RGB operator-(const RGB& lhs, const RGB& rhs) {
    return RGB{ lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b };
}

static RGB operator*(const float scalar, const RGB& rgb) {
    return RGB{ scalar * rgb.r, scalar * rgb.g, scalar * rgb.b };
}

static RGB operator/(const RGB& rgb, const float divisor) {
    return RGB{ rgb.r / divisor, rgb.g / divisor, rgb.b / divisor };
}

// Assigns scaled RGB values to frame buffer on receiving corner colours. This uses the
// equation f(x, y) = a + bx + cy + dxy to fill out the colour values for each pixel.
static ColourRamp construct_colour_ramp(const CornerColours& corner_colours) {
    const RGB top_left = construct_rgb_from_rgb565(corner_colours.top_left);
    const RGB top_right = construct_rgb_from_rgb565(corner_colours.top_right);
    const RGB bottom_left = construct_rgb_from_rgb565(corner_colours.bottom_left);
    const RGB bottom_right = construct_rgb_from_rgb565(corner_colours.bottom_right);

    const RGB a = top_left;
    const RGB b = (top_right - top_left) / 15.0f;
    const RGB c = (bottom_left - top_left) / 8.0f;
    const RGB d = (bottom_right - bottom_left - top_right + top_left) / 120.0f;

    ColourRamp result = {};
    for (int row = 0; row < ColourRamp::HEIGHT; ++row) {
        const float y = static_cast<float>(row);
        for (int column = 0; column < ColourRamp::WIDTH; ++column) {
            const float x = static_cast<float>(column);
            result.colours[row][column] = a + x * b + y * c + x * y * d;
        }
    }

    return result;
}
