#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

#include "function_template.hpp"
#include "class_template_box.hpp"
#include "class_template_animal.hpp"
#include "multiply_template.hpp"


int main(int, char**)
{
    // templates tutorial
    //###################################################

    std::cout << "1) Function template" << std::endl;
    std::cout << "add(2, 3) = " << add(2, 3) << std::endl;          // int
    std::cout << "add(2.5, 3.1) = " << add(2.5, 3.1) << std::endl;  // double
    std::cout << std::endl;


    std::cout << "2) Class template" << std::endl;
    Box<int> int_box(42);
    Box<std::string> str_box("Hello");
    std::cout << "int_box = " << int_box.get_value() << std::endl;
    std::cout << "str_box = " << str_box.get_value() << std::endl;
    std::cout << std::endl;

    Animal<int> giraffe(52342, 8);
    std::cout << "giraffe identifier =  " << giraffe.get_identifier() << std::endl;
    std::cout << "giraffe age =         " << giraffe.get_age() << std::endl;
    std::cout << std::endl;



    Animal<std::string> lion("AAB", 8);
    std::cout << "lion identifier =  " << lion.get_identifier() << std::endl;
    std::cout << "lion age =         " << lion.get_age() << std::endl;
    std::cout << std::endl;




    std::cout << "3) Template specialisation" << std::endl;
    Box<bool> flag(true);
    flag.print_text();  // prints "true"
    flag.set(false);
    flag.print_text();  // prints "false"
    std::cout << std::endl;



    std::cout << "4) C++20 concept with template" << std::endl;
    std::cout << "multiply(3, 4) = " << multiply(3, 4) << std::endl;
    std::cout << "multiply(2.5, 1.5) = " << multiply(2.5, 1.5) << std::endl;
    // multiply(std::string("Hi"), std::string("There")); // ERROR, not a Number
    std::cout << std::endl;


    return 0;
}


