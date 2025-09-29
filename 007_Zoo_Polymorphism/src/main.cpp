
#include <iostream>
#include <memory>

#include "Zoo/Zoo.hpp"
#include "Zoo/Animal.hpp"
#include "Zoo/Aardvark.hpp"
#include "Zoo/Giraffe.hpp"
#include "Zoo/Lion.hpp"
#include "Zoo/Owl.hpp"
#include "Zoo/Tiger.hpp"
#include "Zoo/Zebra.hpp"





int main()
{

    std::cout << "########################" << std::endl;
    std::cout << "      Zoo               " << std::endl;
    std::cout << "########################" << std::endl;


    std::cout << "Make zoo" << std::endl;

    Zoo::Zoo zoo {};
    zoo.set_name("My Zoo");


    std::cout << "Create animals" << std::endl;

    auto zebra = std::make_unique<Zoo::Zebra>("Zippy", 4);
    auto giraffe = std::make_unique<Zoo::Giraffe>("Gerald", 4);
    auto owl = std::make_unique<Zoo::Owl>("Olive", 4);
    auto tiger = std::make_unique<Zoo::Tiger>("Timmy", 14);



    zoo.add_animal(std::move(zebra));
    zoo.add_animal(std::move(giraffe));
    zoo.add_animal(std::move(owl));
    zoo.add_animal(std::move(tiger));

    zoo.list_animals();


    return 0;
}





