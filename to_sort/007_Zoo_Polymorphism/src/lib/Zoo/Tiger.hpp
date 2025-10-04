#ifndef TIGER_HPP
#define TIGER_HPP

#include "Animal.hpp"

namespace Zoo 
{

class Tiger : public Animal 
{

public:

    Tiger(const std::string& name, size_t age) : Animal(name, age) {}

    std::string get_type() const override { return "Tiger"; }

    void eat(size_t meal_counter) override
    {
        _food_eaten = meal_counter * 2.1;  // kg
    };

};

}

#endif
