#include "input_check.h"

#include <cstring>

template <typename T>
struct Maybe {
    T value;
    bool is_valid;
};

static bool is_decimal_digit(const char c) {
    return '0' <= c && c <= '9';
}

static Maybe<unsigned short> parse_decimal(const char* const arg) {
    Maybe<unsigned short> result = {};

    const std::size_t char_count = std::strlen(arg);
    if (char_count == 0 || char_count > 5) {
        return result;
    }

    for (std::size_t i = 0; i < char_count; ++i) {
        if (!is_decimal_digit(arg[i])) {
            return result;
        }
    }

    unsigned short multiplier = 1;
    for (std::size_t i = char_count; i > 0; --i) {
        const unsigned short digit_value = static_cast<unsigned short>(arg[i - 1] - '0');
        result.value += digit_value * multiplier;
        multiplier *= 10;
    }

    result.is_valid = true;
    return result;
}

static bool is_hexadecimal_digit(const char c) {
    return is_decimal_digit(c) || ('A' <= c && c <= 'F');
}

static unsigned short hexadecimal_digit_to_value(const char c) {
    const bool is_dec = is_decimal_digit(c);
    return static_cast<unsigned short>(is_dec) * (c - '0') + static_cast<unsigned short>(!is_dec) * (c - 'A' + 10);
}

static Maybe<unsigned short> parse_hexadecimal(const char* const arg) {
    Maybe<unsigned short> result = {};

    const std::size_t char_count = std::strlen(arg);
    if (char_count < 3 || char_count > 6 || arg[0] != '0' || arg[1] != 'x') {
        return result;
    }

    for (std::size_t i = 2; i < char_count; ++i) {
        if (!is_hexadecimal_digit(arg[i])) {
            return result;
        }
    }

    unsigned short multiplier = 1;
    for (std::size_t i = char_count - 1; i >= 2; --i) {
        const char digit = arg[i];
        const unsigned short digit_value = hexadecimal_digit_to_value(digit);
        result.value += digit_value * multiplier;
        multiplier *= 16;
    }

    result.is_valid = true;
    return result;
}

struct ParseColourArgumentResult {
    RGB565 colour;
    const char* error;
};

static ParseColourArgumentResult parse_colour_argument(const char* const arg) {
    ParseColourArgumentResult result = {};

    const Maybe<unsigned short> decimal_value = parse_decimal(arg);
    const Maybe<unsigned short> hexadecimal_value = parse_hexadecimal(arg);
    if (decimal_value.is_valid) {
        result.colour = decimal_value.value;
    } else if (hexadecimal_value.is_valid) {
        result.colour = hexadecimal_value.value;
    } else {
        result.error = "Colour argument is not a decimal/hexadecimal number in the format dddddd/0xhhhh where d -> 0,..,9 and h -> 0,..,9,A,..F.";
    }

    return result;
}

// Checks user inputs and returns corner RGB565 values for colour ramp.
static ParseUserInputResult parse_user_input(const int argc, const char* argv[]) {
    ParseUserInputResult result = {};
    if ((argc < 3) || (argc > 5)) {
        result.error = "Invalid number of arguments.";
        return result;
    }

    const ParseColourArgumentResult top_left_parse_result = parse_colour_argument(argv[1]);
    if (top_left_parse_result.error != nullptr) {
        result.error = top_left_parse_result.error;
        return result;
    }

    result.corner_colours.top_left = top_left_parse_result.colour;

    const ParseColourArgumentResult top_right_parse_result = parse_colour_argument(argv[2]);
    if (top_right_parse_result.error != nullptr) {
        result.error = top_right_parse_result.error;
        return result;
    }

    result.corner_colours.top_right = top_right_parse_result.colour;

    switch (argc) {
        case 3: {
            result.corner_colours.bottom_left = result.corner_colours.top_left;
            result.corner_colours.bottom_right = result.corner_colours.top_right;
            break;
        }

        case 4: {
            const ParseColourArgumentResult bottom_left_parse_result = parse_colour_argument(argv[3]);
            if (bottom_left_parse_result.error != nullptr) {
                result.error = bottom_left_parse_result.error;
                return result;
            }

            result.corner_colours.bottom_left = bottom_left_parse_result.colour;
            result.corner_colours.bottom_right = result.corner_colours.top_right;
            break;
        }

        case 5: {
            const ParseColourArgumentResult bottom_left_parse_result = parse_colour_argument(argv[3]);
            if (bottom_left_parse_result.error != nullptr) {
                result.error = bottom_left_parse_result.error;
                return result;
            }

            result.corner_colours.bottom_left = bottom_left_parse_result.colour;

            const ParseColourArgumentResult bottom_right_parse_result = parse_colour_argument(argv[4]);
            if (bottom_right_parse_result.error != nullptr) {
                result.error = bottom_right_parse_result.error;
                return result;
            }

            result.corner_colours.bottom_right = bottom_right_parse_result.colour;
            break;
        }
    }

    return result;
}
