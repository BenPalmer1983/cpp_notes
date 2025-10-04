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


    /*
    // Future - forward arguments to emplace_back
    template<typename... Args>
    void add_animal(Args&&... args) 
    {
        _animals.emplace_back(std::forward<Args>(args)...);
    }
    */


};

}

#endif 