#ifndef OWL_HPP
#define OWL_HPP

#include "Animal.hpp"

namespace Zoo 
{

class Owl : public Animal 
{

public:

    Owl(const std::string& name, size_t age) : Animal(name, age) {}

    std::string get_type() const override { return "Owl"; }
    
};

}

#endif
