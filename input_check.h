#pragma once

#include "colour_ramp.h"

struct ParseUserInputResult {
	CornerColours corner_colours;
	const char* error;
};

static ParseUserInputResult parse_user_input(int argc, const char* argv[]);
