#ifndef LION_HPP
#define LION_HPP

#include "Animal.hpp"

namespace Zoo 
{

class Lion : public Animal 
{

public:

    Lion(const std::string& name, size_t age) : Animal(name, age) {}

    std::string get_type() const override { return "Lion"; }
    

    void eat(size_t meal_counter) override
    {
        _food_eaten = meal_counter * 1.0;  // kg
    };

};

} 
#endif
