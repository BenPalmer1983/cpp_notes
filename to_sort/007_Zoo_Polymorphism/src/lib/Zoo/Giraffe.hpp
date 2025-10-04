#ifndef GIRAFFE_HPP
#define GIRAFFE_HPP

#include "Animal.hpp"

namespace Zoo 
{

class Giraffe : public Animal 

{
public:

    Giraffe(const std::string& name, size_t age) : Animal(name, age) {}

    std::string get_type() const override { return "Giraffe"; }


    void eat(size_t meal_counter) override
    {
        _food_eaten = meal_counter * 1.5;  // kg
    };

};


} 

#endif
