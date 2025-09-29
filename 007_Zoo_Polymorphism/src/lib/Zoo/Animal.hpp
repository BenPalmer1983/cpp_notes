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

    std::string _name;
    size_t _age;

public:
    Animal(const std::string& name, size_t age)
        : _name(name), _age(age) {}

    virtual ~Animal() = default;


    const std::string& get_name() const { return _name; }

    size_t get_age() const { return _age; }



    // Virtual functions
    virtual std::string get_type() const = 0;

};

} 

#endif 