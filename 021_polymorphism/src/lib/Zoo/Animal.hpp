#ifndef ANIMAL_HPP
#define ANIMAL_HPP

/*********************************************************************************************************************************/
#include <algorithm>
#include <iostream>
#include <stdexcept>
/*********************************************************************************************************************************/

namespace Zoo 
{

class Animal 
{

protected:

    std::string _name {};
    size_t _age {};
    double _food_eaten {};

public:
    Animal(const std::string& name, size_t age)
        : _name(name), _age(age) {}

    virtual ~Animal() = default;


    const std::string& get_name() const { return _name; }
    size_t get_age() const { return _age; }
    double get_food_eaten() const { return _food_eaten; }



    // Virtual functions
    virtual std::string get_type() const = 0;
    virtual void eat(size_t meal_counter) = 0;

};

} 

#endif 