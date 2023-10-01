#pragma once

#include "colour_ramp.h"

static void print_rgb565_values_to_console(const ColourRamp& colour_ramp);

struct Vec2 {
    float x;
    float y;
};

struct Vertex {
    Vec2 position;
    RGB colour;
};

static constexpr int COLOUR_RAMP_TILE_COUNT = ColourRamp::WIDTH * ColourRamp::HEIGHT;

struct Vertices {
    Vertex buffer[4 * COLOUR_RAMP_TILE_COUNT];
};

static Vertices construct_vertices_for_colour_ramp(const ColourRamp& colour_ramp);

struct Indices {
    unsigned short buffer[6 * COLOUR_RAMP_TILE_COUNT];
};

static Indices construct_indices_for_colour_ramp();
