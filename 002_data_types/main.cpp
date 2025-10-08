
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{

    // Variables can be created where they are needed

    // Integers

    std::cout << "Create an integer and use default value (0)." <<std::endl;
    int my_integer_a {};
    std::cout << "my_integer_a: " << my_integer_a << "\n" << std::endl;


    std::cout << "Create an integer and give a value (10)." <<std::endl;
    int my_integer_b {10};
    std::cout << "my_integer_b: " << my_integer_b << "\n" << std::endl;


    std::cout << "Change value to 100." <<std::endl;
    my_integer_b = 100;
    std::cout << "my_integer_b: " << my_integer_b << "\n" << std::endl;



    // Booleans

    std::cout << "Create a bool (default is true)." <<std::endl;
    bool flag_a {};
    if(flag_a)
    {
        std::cout << "flag_a is true" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Create a bool give value false." <<std::endl;
    bool flag_b {false};
    if(!flag_b)
    {
        // Integer is defined in the if block
        int only_defined_in_if_block {1234};
        std::cout << "flag_b is false" << std::endl;
        std::cout << only_defined_in_if_block << std::endl;
    }

    // only_defined_in_if_block is now out of scope
    // std::cout << only_defined_in_if_block << std::endl; would cause an error



    // Doubles
    std::cout << "Create a double with default value." <<std::endl;
    int my_double {};
    std::cout << "my_double: " << my_double << "\n" << std::endl;


    std::cout << "Change value to 123.4" <<std::endl;
    my_double = 123.4;
    std::cout << "my_double: " << my_double << "\n" << std::endl;


    // Strings
    std::cout << "Create a string." <<std::endl;
    std::string my_string_a {};
    std::cout << "my_string_a: " << my_string_a <<std::endl;


    // Strings
    std::cout << "Create a string." <<std::endl;
    std::string my_string_b {"test string 1234"};
    std::cout << "my_string_b: " << my_string_b <<std::endl;




}





