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

private:

    std::string _name {};
    std::string _type {};
    size_t _age {};


public:

    Animal (const std::string& name, const std::string& type, size_t age) :
                            _name(name), _type(type), _age(age) {}


    void set_name(const std::string& name)
    {
        _name = std::move(name);
    }

    void set_type(const std::string& type)
    {
        _type = std::move(type);
    }

    void set_age(size_t age)
    {
        _age = age;
    }

    // Immutable
    const std::string& get_name() const 
    {
        return _name;
    }

    // Mutable
    std::string& get_name() 
    {
        return _name;
    }

    // Copy
    std::string get_name_copy() const 
    {
        return _name;
    }

    std::string get_type() const
    {
        return _name;
    }

    size_t get_age()
    {
        return _age;
    }




};

}

#endif 