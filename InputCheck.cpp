#include <iostream>

#include "InputCheck.h"

using namespace std;

bool is_dec_or_hex(const char* x) //Checks if *x is a decimal or hexadecimal number
{
    if(x[0] == '0' && x[1] == 'x') //If *x is in the form of 0xf43d2d, function returns false if any char from the 3rd position
    {                              //onwards is not a hex digit
        for(int i = 2; x[i] != '\0'; i++)
        {
            if(!isxdigit(x[i])){return false;}
        }
    }
    else //Else it returns false if any characters in *x are not a decimal digit
    {
        for(int i = 0; x[i] != '\0'; i++)
        {
            if(!isdigit(x[i])){return false;}
        }
    }
    return true;
}

bool check_arg_count(int &argc)
{
    if(argc <= 3 || argc > 6)
    {
        cout << "Error: Invalid number of arguments." << endl;
        return false;
    }

    return true;
}

bool check_display_name(const char* x)
{
    if(is_dec_or_hex(x))
    {
        cout << "Error: Display name is not valid or not specified.";
        return false;
    }

    return true;
}

bool check_if_numbers(int &argc, char** argv)
{
    for(int i = 2; i < argc; i++)
    {
        if(!is_dec_or_hex(argv[i]))
        {
            cout << "Error: Argument " << i + 1 << " is not a number in the specified decimal or hexadecimal format.";
            return false;
        }
    }

    return true;
}

bool check_if_colours_valid(long arr[])
{
    for(int i = 0; i < 4; i++)
    {
        if(arr[i] < 0 || arr[i] > 65535)
        {
            cout << "Error: Please specify colour values between 0 (0x0000) and 65535 (0xFFFF)" << endl;
            return false;
        }
    }

    return true;
}
