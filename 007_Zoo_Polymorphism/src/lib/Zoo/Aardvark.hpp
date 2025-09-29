#ifndef AARDVARK_HPP
#define AARDVARK_HPP

#include "Animal.hpp"

namespace Zoo 
{

class Aardvark : public Animal 
{

public:
    Aardvark(const std::string& name, size_t age) : Animal(name, age) {}

    // const - this is a read only method
    // override - will override a virtual function
    std::string get_type() const override { return "Aardvark"; }


    // override - will override a virtual function
    void eat(size_t meal_counter) override
    {
        _food_eaten = meal_counter * 0.2;  // kg
    };

};

} // namespace Zoo

#endif
