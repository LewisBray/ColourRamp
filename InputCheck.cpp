#include "inputcheck.h"

#include <regex>
#include <sstream>
#include <iostream>


// Checks if string holds a hexadecimal number.
static bool IsHex(const char* const arg)
{
    std::regex hexExpr("-?0x[0-9a-f]+", std::regex_constants::icase);
    return std::regex_match(arg, hexExpr);
}


// Checks if string holds decimal number.
static bool IsDec(const char* const arg)
{
    std::regex decExpr("-?[0-9]+");
    return std::regex_match(arg, decExpr);
}


// Checks user inputs and returns corner RGB565 values for colour ramp.
CornerColours ParseInputs(const int argc, const char* const argv[])
{
    if ((argc < 4) || (argc > 6))
        throw Error("Invalid number of arguments.");

    if (IsDec(argv[1]) || IsHex(argv[1]))
        throw Error("Display name is invalid or not specified.");

    unsigned long long inputNums[4];
    for (int i = 2; i < argc; ++i)  // Check every numerical arg
        if (IsDec(argv[i])) {
            std::stringstream colour;
            colour << argv[i];
            colour >> inputNums[i - 2];
        }
        else if (IsHex(argv[i])) {
            const std::string hexVal{ &argv[i][2] };
            std::stringstream colour;
            colour << std::hex << hexVal;
            colour >> inputNums[i - 2];
        }
        else {
            std::string errMsg{ argv[i] };
            errMsg += " is not a decimal/hexadecimal number.";
            throw Error{ errMsg };
        }

    for (int i = 2; i < argc; ++i)
    {
        const bool isNegative = ((argv[i][0] == '-') && (argv[i][0] != '0'));
        if (isNegative || (inputNums[i - 2] > 0xFFFF)) {
            std::string errMsg{ argv[i] };
            errMsg += " is not in the range 0 (0x0000) to 65535 (0xFFFF).";
            throw Error{ errMsg };
        }
    }

    switch (argc) {
        case 4: inputNums[2] = inputNums[0];
        case 5: inputNums[3] = inputNums[1];
    }

    unsigned short rgb565Colours[4];
    for (int i = 0; i < 4; ++i)
        rgb565Colours[i] = static_cast<unsigned short>(inputNums[i]);

    return CornerColours{ rgb565Colours };
}
