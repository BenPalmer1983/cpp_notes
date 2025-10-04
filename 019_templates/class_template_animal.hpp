#pragma once

template <typename T>
class Animal
{

private:
    T _identifier {};
    int _age {};

public:

    Animal(T identifier, int age) : _identifier(identifier), _age(age) {}

    void set_identifier(T identifier) 
    { 
        _identifier = identifier; 
    }

    void set_age(int age) 
    { 
        _age = age; 
    }

    T get_identifier() const 
    { 
        return _identifier; 
    }

    int get_age() const 
    { 
        return _age; 
    }

};

