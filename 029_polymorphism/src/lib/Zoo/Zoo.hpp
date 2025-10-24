#ifndef ZOO_HPP
#define ZOO_HPP

/*********************************************************************************************************************************/
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

#include "Animal.hpp"
/*********************************************************************************************************************************/

namespace Zoo
{


class Zoo 
{

private:

    std::string _name {};
    std::vector<std::unique_ptr<Animal>> _animals;


public:

    // Setters/Getters

    void set_name(const std::string& name)
    {
        _name = std::move(name);
    }

    std::string get_name()
    {
        return _name;
    }

    std::vector<std::unique_ptr<Animal>>& get_animals()
    {
        return _animals;
    }


    void add_animal(std::unique_ptr<Animal> animal) 
    {
        _animals.emplace_back(std::move(animal));
    }

    // List animals
    void list_animals() const 
    {
        for (const auto& animal : _animals) 
        {
            std::cout << &animal << ","
                      << animal->get_type() << ","
                      << animal->get_name() << ","
                      << animal->get_age() << ","
                      << animal->get_food_eaten() << "\n";
        }
        std::cout << std::flush;
    }

};

}

#endif 