#ifndef ERROR_HPP
#define ERROR_HPP


#include <iostream>
#include <stdexcept>
#include <string>

// Helper for stringification
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// Macro to throw std::invalid_argument with context
#define THROW_INVALID_ARGUMENT(msg) \
    throw std::invalid_argument( \
        std::string("[invalid_argument] ") + msg + \
        " | File: " + __FILE__ + \
        ", Line: " + TOSTRING(__LINE__) + \
        ", Function: " + __func__ \
    )



#endif