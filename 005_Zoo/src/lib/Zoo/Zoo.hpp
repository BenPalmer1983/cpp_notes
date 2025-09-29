#ifndef ZOO_HPP
#define ZOO_HPP

/*********************************************************************************************************************************/
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Animal.hpp"
/*********************************************************************************************************************************/

namespace Zoo
{


class Zoo 
{

private:

    std::string _name {};
    std::vector<Animal> _animals {};


public:

    // Setters/Getters

    // Instance method (non-static function) i.e. belongs to an instance of the class (object)
    void set_name(const std::string& name)
    {
        _name = std::move(name);
    }

    std::string get_name()
    {
        return _name;
    }

    std::vector<Animal>& get_animals()
    {
        return _animals;
    }


    // Add animal
    void add_animal(Animal animal)
    {
        _animals.emplace_back(std::move(animal));
    }

    // List animals
    void list_animals() const 
    {
        for (const auto& animal : _animals) 
        {
            std::cout << &animal << ","
                      << animal.get_type() << ","
                      << animal.get_name() << ","
                      << animal.get_age() << "\n";
        }
        std::cout << std::flush;
    }



};

}

#endif 