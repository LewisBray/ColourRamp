#pragma once

#include "colourramp.h"

#include <string>


// Simple struct to throw as an exception to avoid throwing raw string.
struct Error
{
    explicit Error(const std::string& errMsg)
        : message{ errMsg }
    {}

    std::string message;
};

CornerColours ParseInputs(const int argc, const char* const argv[]);
