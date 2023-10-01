#pragma once

using RGB565 = unsigned short;

struct RGB {
    float r;
    float g;
    float b;
};

static RGB construct_rgb_from_rgb565(RGB565 rgb565);
static RGB565 construct_rgb565_from_rgb(const RGB& rgb);

static RGB operator+(const RGB& lhs, const RGB& rhs);
static RGB operator-(const RGB& lhs, const RGB& rhs);
static RGB operator*(float scalar, const RGB& rgb);
static RGB operator/(const RGB& rgb, float divisor);

struct CornerColours {
    RGB565 top_left;
    RGB565 top_right;
    RGB565 bottom_left;
    RGB565 bottom_right;
};

struct ColourRamp {
    static constexpr int WIDTH = 16;
    static constexpr int HEIGHT = 9;
    RGB colours[HEIGHT][WIDTH];
};

static ColourRamp construct_colour_ramp(const CornerColours& corner_colours);
