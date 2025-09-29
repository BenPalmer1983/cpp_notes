
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    std::cout << "Number of arguments: " << argc << std::endl;

    for (int i = 0; i < argc; i++) 
    {
        std::string argument_string = argv[i];
        std::cout << "Argument " << i << ": " << argument_string << std::endl;
    }

    return 0;
}





