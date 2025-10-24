
#include <iostream>

#include "Zoo/Zoo.hpp"
#include "Zoo/ZooEngine.hpp"
#include "Zoo/Animal.hpp"





int main()
{

    std::cout << "########################" << std::endl;
    std::cout << "      Zoo               " << std::endl;
    std::cout << "########################" << std::endl;


    std::cout << "Make zoo" << std::endl;

    Zoo::Zoo zoo {};
    zoo.set_name("My Zoo");


    std::cout << "Create animals" << std::endl;

    Zoo::Animal zebra {"Zippy", "Zebra", 9};
    Zoo::Animal tiger {"Timmy", "Tiger", 14};
    Zoo::Animal giraffe {"Gerald", "Giraffe", 4};
    Zoo::Animal owl {"Olive", "Owl", 22};

    std::cout << "Zebra location: " << &zebra << std::endl;
    zebra.memory();
    zoo.add_animal(zebra);
    zoo.add_animal(giraffe);
    zoo.add_animal(owl);
    zoo.add_animal(tiger);

    // std::vector<Animal>& animals = zoo.get_animals(); (or use auto - below)
    auto animals_read_only = zoo.get_animals();

    const auto& zebra_in_zoo = animals_read_only[0];
    std::cout << "Zebra location: " << &zebra_in_zoo << std::endl;
    zebra_in_zoo.memory();

    zoo.list_animals();
    std::cout << "####" << std::endl;



    // Get animals (mutable)

    auto& animals = zoo.get_animals();
    Zoo::ZooEngine::sort_by_name_asc(animals);      // Sort with ZooEngine
    zoo.list_animals();
    std::cout << "####" << std::endl;

    Zoo::ZooEngine::sort_by_name_desc(animals);      // Sort with ZooEngine
    zoo.list_animals();
    std::cout << "####" << std::endl;

    Zoo::ZooEngine::sort_by_age_asc(animals);      // Sort with ZooEngine
    zoo.list_animals();
    std::cout << "####" << std::endl;

    Zoo::ZooEngine::sort_by_age_desc(animals);      // Sort with ZooEngine
    zoo.list_animals();
    std::cout << "####" << std::endl;


    return 0;
}





