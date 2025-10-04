
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Zoo/Animal.hpp"



int main(int argc, char* argv[])
{

    // Uniques pointers
    //

    std::cout << "Unique Pointers" << std::endl;

    std::unique_ptr<Zoo::Animal> giraffe = std::make_unique<Zoo::Animal>("Gerald", "Giraffe", 12);
    std::cout << giraffe->get_name() << std::endl;
    std::cout << "Mem loc of pointer:         " << &giraffe << std::endl;
    std::cout << "Mem loc of raw pointer:     " << giraffe.get() << std::endl;

    // Cannot copy a pointer to giraffe (it's unique)
    // std::unique_ptr<Zoo::Animal> another_pointer_to_giraffe = giraffe;

    // Can move
    std::unique_ptr<Zoo::Animal> another_pointer_to_giraffe = std::move(giraffe);
    
    std::cout << "Mem loc of pointer:         " << &giraffe << std::endl;
    std::cout << "Mem loc of raw pointer:     " << giraffe.get() << std::endl;

    std::cout << "Mem loc of pointer (moved):         " << &another_pointer_to_giraffe << std::endl;
    std::cout << "Mem loc of raw pointer (moved):     " << another_pointer_to_giraffe.get() << std::endl;


    std::cout << "" << std::endl;
    std::cout << "" << std::endl;


    // Shared pointers
    //

    std::cout << "Shared Pointers" << std::endl;

    std::shared_ptr<Zoo::Animal> aardvark = std::make_shared<Zoo::Animal>("Arthur", "Aardvark", 5);
    std::cout << aardvark->get_name() << std::endl;
    std::cout << "Mem loc of pointer:              " << &aardvark << std::endl;
    std::cout << "Mem loc of raw pointer:          " << aardvark.get() << std::endl;
    
    std::shared_ptr<Zoo::Animal> aardvark_copy = aardvark;
    std::cout << aardvark_copy->get_name() << std::endl;
    std::cout << "Mem loc of pointer:              " << &aardvark << std::endl;
    std::cout << "Mem loc of raw pointer:          " << aardvark.get() << std::endl;
    std::cout << "Mem loc of pointer copy:         " << &aardvark_copy << std::endl;
    std::cout << "Mem loc of raw pointer copy:     " << aardvark_copy.get() << std::endl;


    return 0;
}





