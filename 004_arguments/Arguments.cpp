// =========================================================
//  Arguments.cpp
//  How to handle command line arguments in C++
// =========================================================

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    // argc — argument count (number of arguments)
    // argv — argument vector (array of C-style strings)
    //
    // argv[0] is always the name of the program itself.
    // argv[1], argv[2], ... contain any extra arguments.

    std::cout << "Number of arguments: " << argc << std::endl;

    // Loop through each argument (more on for loops later)
    for (int i = 0; i < argc; i++) 
    {
        // Convert C-style string (char*) to std::string
        std::string argument_string {argv[i]};

        std::cout << "Argument " << i << ": " << argument_string << std::endl;
    }

    std::cout << "\n";

    // Example: use argument if one was provided
    // (more on if statements later)
    if (argc > 1)
    {
        std::string first_argument {argv[1]};
        std::cout << "First user argument: " << first_argument << std::endl;
    }
    else
    {
        std::cout << "No extra arguments provided." << std::endl;
    }

    std::cout << std::endl;
    return 0;
}




