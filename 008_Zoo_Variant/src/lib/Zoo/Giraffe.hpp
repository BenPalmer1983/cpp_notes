#ifndef GIRAFFE_HPP
#define GIRAFFE_HPP

/*********************************************************************************************************************************/
#include <algorithm>
#include <iostream>
#include <stdexcept>
/*********************************************************************************************************************************/

namespace Zoo
{


class Giraffe 
{

private:

    std::string _name {};
    size_t _age {};


public:

    Giraffe (const std::string& name, const std::string& type, size_t age) :
                            _name(name), _age(age) {}


    void set_name(const std::string& name)
    {
        _name = std::move(name);
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

    const std::string& get_type() const
    {
        return "Giraffe";
    }

    size_t get_age() const
    {
        return _age;
    }


    void memory() const
    {
        std::cout << "   name at:        " << &_name << std::endl;
        std::cout << "   age at:         " << &_age << std::endl;
    }



};

}

#endif 