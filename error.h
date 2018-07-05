#pragma once

#include <string>


// Simple struct to throw as an
// exception to avoid throwing raw strings.
struct Error
{
    explicit Error(const std::string& errMsg)
        : message{ errMsg }
    {}

    std::string message;
};