#ifndef ZEBRA_HPP
#define ZEBRA_HPP

#include "Animal.hpp"

namespace Zoo 
{

class Zebra : public Animal 
{

public:
    Zebra(const std::string& name, size_t age) : Animal(name, age) {}
    std::string get_type() const override { return "Zebra"; }
};

}

#endif
