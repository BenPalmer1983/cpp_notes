#ifndef AARDVARK_HPP
#define AARDVARK_HPP

#include "Animal.hpp"

namespace Zoo 
{

class Aardvark : public Animal 
{

public:
    Aardvark(const std::string& name, size_t age) : Animal(name, age) {}

    std::string get_type() const override { return "Aardvark"; }

};

} // namespace Zoo

#endif
