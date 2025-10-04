#ifndef ZOO_HPP
#define ZOO_HPP

/*********************************************************************************************************************************/
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <variant>
#include <vector>

#include "Aardvark.hpp"
#include "Giraffe.hpp"
#include "Owl.hpp"
#include "Tiger.hpp"
#include "Zebra.hpp"
/*********************************************************************************************************************************/

namespace Zoo
{

using Animal = std::variant<Aardvark, Giraffe, Owl, Tiger, Zebra>;

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
            std::visit([](const auto& animal_address) {
                std::cout << static_cast<const void*>(&animal_address) << ","
                          << a.get_type() << ","
                          << a.get_name() << ","
                          << a.get_age()  << "\n";
            }, animal);
        }
        std::cout << std::flush;
    }



};

}

#endif 