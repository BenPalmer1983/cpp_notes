#pragma once

#include <iostream>

// Template for Box
template <typename T>
class Box
{

private:
    T _value;

public:

    Box(T value) : _value(value) {}

    void set(T value) 
    { 
        _value = value; 
    }

    T get_value() const 
    { 
        return _value; 
    }

};

// A special class for bool versions
template <>
class Box<bool>
{
private:
    bool _flag;

public:
    Box(bool flag) : _flag(flag) {}

    bool get_flag() const 
    { 
        return _flag;     
    }

    void set(bool flag) 
    { 
        _flag = flag; 
    }

    void print_text() const
    {
        std::cout << (_flag ? "true" : "false") << std::endl;
    }

};





