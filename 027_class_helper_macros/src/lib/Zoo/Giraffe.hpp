#ifndef GIRAFFE_HPP
#define GIRAFFE_HPP

/*********************************************************************************************************************************/
#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "Helper/_helper.hpp"
/*********************************************************************************************************************************/

namespace Zoo
{


class Giraffe 
{

private:

    std::string _name {};
    size_t _age {};
    std::string _type {"Giraffe"};


public:

    Giraffe (const std::string& name, size_t age) :
                            _name(name), _age(age) {}


    STRING_SET_GET(name);
    SIZE_T_SET_GET(age);
    STRING_GET_RO(type);


    void memory() const
    {
        std::cout << "   name at:        " << &_name << std::endl;
        std::cout << "   age at:         " << &_age << std::endl;
        std::cout << "   type at:         " << &_type << std::endl;
    }



};

}

#endif 