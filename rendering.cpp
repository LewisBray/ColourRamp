#include "rendering.h"

#include <cstdlib>
#include <cstdio>

static void print_rgb565_values_to_console(const ColourRamp& colour_ramp) {
    char colour_ramp_string[7 * COLOUR_RAMP_TILE_COUNT];    // 7 bytes for "0xhhhh" and an additional ' ', '\n' or '\0' per value
    for (int row = 0; row < ColourRamp::HEIGHT; ++row) {
        const int row_offset = row * ColourRamp::WIDTH * 7;
        for (int column = 0; column < ColourRamp::WIDTH; ++column) {
            const RGB565 rgb565 = construct_rgb565_from_rgb(colour_ramp.colours[row][column]);
            const int offset = 7 * column;
            std::sprintf(colour_ramp_string + row_offset + offset, "0x%04X", rgb565);
            colour_ramp_string[row_offset + offset + 6] = ' ';
        }

        colour_ramp_string[row_offset + ColourRamp::WIDTH * 7 - 1] = '\n';
    }
    
    colour_ramp_string[7 * COLOUR_RAMP_TILE_COUNT - 1] = '\0';
    std::puts(colour_ramp_string);
}

static Vertices construct_vertices_for_colour_ramp(const ColourRamp& colour_ramp) {
    Vertices vertices = {};
    for (int row = 0; row < ColourRamp::HEIGHT; ++row) {
        const float y = static_cast<float>(row);
        for (int column = 0; column < ColourRamp::WIDTH; ++column) {
            const float x = static_cast<float>(column);

            const int tile_index = ColourRamp::WIDTH * row + column;
            const int vertex_index = 4 * tile_index;

            const RGB& colour = colour_ramp.colours[row][column];
            Vertex& bottom_left = vertices.buffer[vertex_index + 0];
            bottom_left.position.x = x;
            bottom_left.position.y = y;
            bottom_left.colour = colour;

            Vertex& bottom_right = vertices.buffer[vertex_index + 1];
            bottom_right.position.x = x + 1.0f;
            bottom_right.position.y = y;
            bottom_right.colour = colour;

            Vertex& top_right = vertices.buffer[vertex_index + 2];
            top_right.position.x = x + 1.0f;
            top_right.position.y = y + 1.0f;
            top_right.colour = colour;

            Vertex& top_left = vertices.buffer[vertex_index + 3];
            top_left.position.x = x;
            top_left.position.y = y + 1.0f;
            top_left.colour = colour;
        }
    }

    return vertices;
}

static Indices construct_indices_for_colour_ramp() {
    Indices indices = {};
    for (int tile_index = 0; tile_index < COLOUR_RAMP_TILE_COUNT; ++tile_index) {
        indices.buffer[6 * tile_index + 0] = 4 * tile_index + 0;
        indices.buffer[6 * tile_index + 1] = 4 * tile_index + 1;
        indices.buffer[6 * tile_index + 2] = 4 * tile_index + 2;
        indices.buffer[6 * tile_index + 3] = 4 * tile_index + 2;
        indices.buffer[6 * tile_index + 4] = 4 * tile_index + 3;
        indices.buffer[6 * tile_index + 5] = 4 * tile_index + 0;
    }

    return indices;
}
