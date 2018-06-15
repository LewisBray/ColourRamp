#include "colourramp.h"
#include "inputcheck.h"

#include <iostream>


int main(int argc, char* argv[])
{
    CornerColours inputVals;

    try {
        inputVals = ParseInputs(argc, argv);
    }
    catch (const Error& error) {
        std::cout << "Error: " << error.message << "\n";
        return -1;
    }

    ColourRamp display{ inputVals };

    return 0;
}
