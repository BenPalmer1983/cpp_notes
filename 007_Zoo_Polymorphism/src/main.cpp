
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

    // Create Zoo::Zebra zebra on the heap
    std::unique_ptr<Zoo::Zebra> zebra(new Zoo::Zebra("Zippy", 4));

    // Alternatively
    auto giraffe = std::make_unique<Zoo::Giraffe>("Gerald", 4);
    auto owl = std::make_unique<Zoo::Owl>("Olive", 4);
    auto tiger = std::make_unique<Zoo::Tiger>("Timmy", 14);

    // Feed animals
    zebra->eat(3);
    owl->eat(2);
    tiger->eat(5);

    std::cout << "Adding animals to Zoo." << std::endl;

    zoo.add_animal(std::move(zebra));
    zoo.add_animal(std::move(giraffe));
    zoo.add_animal(std::move(owl));
    zoo.add_animal(std::move(tiger));


    std::cout << "Zoo in memory:  " << &zoo << std::endl;
    zoo.list_animals();


    return 0;
}





