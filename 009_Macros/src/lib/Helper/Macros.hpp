#ifndef MACROS_HPP
#define MACROS_HPP


/*********************************************************************************************************************************/
#include <string>
/*********************************************************************************************************************************/



#define CLASS_SET_GET(Class, attribute) \
    /* Setters (lvalues, rvalues) */ \
    inline void set_##attribute(const Class& attribute) {  _##attribute = attribute; } \
    inline void set_##attribute(Class&& attribute) noexcept( noexcept(_##attribute = std::move(attribute))) {  _##attribute = std::move(attribute); } \
    /* Getters read/write, readonly, copy */ \
    Class& get_##attribute() { return _##attribute; } \
    const Class& get_##attribute() const { return _##attribute; } \
    Class get_##attribute##_copy() const { return _##attribute; }

#define STRING_SET_GET(attribute) \
    /* Setters (lvalues, rvalues) */ \
    inline void set_##attribute(const std::string& attribute) {  _##attribute = attribute; } \
    inline void set_##attribute(std::string&& attribute) noexcept( noexcept(_##attribute = std::move(attribute))) {  _##attribute = std::move(attribute); } \
    /* Getters read/write, readonly, copy */ \
    std::string& get_##attribute() { return _##attribute; } \
    const std::string& get_##attribute() const { return _##attribute; } \
    std::string get_##attribute##_copy() const { return _##attribute; }

#define STRING_GET(attribute) \
    /* Getters read/write, readonly, copy */ \
    std::string& get_##attribute() { return _##attribute; } \
    const std::string& get_##attribute() const { return _##attribute; } \
    std::string get_##attribute##_copy() const { return _##attribute; }

#define STRING_GET_RO(attribute) \
    /* Getters readonly, copy */ \
    const std::string& get_##attribute() const { return _##attribute; } \
    std::string get_##attribute##_copy() const { return _##attribute; }

#define DOUBLE_SET_GET(attribute)                                            \
    inline void set_##attribute(double attribute) { _##attribute = attribute; } \
    double get_##attribute() const { return _##attribute; }

#define DOUBLE_SET(attribute)                                            \
    inline void set_##attribute(double attribute) { _##attribute = attribute; } \
    
#define DOUBLE_GET(attribute)                                            \
    double get_##attribute() const { return _##attribute; }

#define DOUBLE_SET_GET_INV(attribute)                                            \
    inline void set_##attribute(double attribute) { _##attribute = attribute; _inv_##attribute = 1.0 / attribute;  } \
    double get_##attribute() const { return _##attribute; } \
    double get_inv_##attribute() const { return _inv_##attribute; }

#define INT_SET_GET(attribute)                                            \
    inline void set_##attribute(int attribute) { _##attribute = attribute; } \
    int get_##attribute() const { return _##attribute; }

#define SIZE_T_SET_GET(attribute)                                            \
    inline void set_##attribute(size_t attribute) { _##attribute = attribute; } \
    size_t get_##attribute() const { return _##attribute; }

#define BOOL_SET_GET(attribute)                                            \
    inline void set_##attribute(bool attribute) { _##attribute = attribute; } \
    bool get_##attribute() const { return _##attribute; }


#define SINGLETON(Class)  \
    class Class##Once  \
    {  \
    public:  \
        inline static Class& get() { static Class instance; return instance; }   \
        inline static const Class& get_ro() { return get(); }   \
    private: \
        Class##Once() {}; \
        ~Class##Once() = default; \
        Class##Once(const Class##Once&) = delete; \
        Class##Once& operator=(const Class##Once&) = delete; \
        Class##Once(Class##Once&&) = delete; \
        Class##Once& operator=(const Class##Once&&) = delete; \
    };



#define ITERATOR(Type, attribute) \
    std::vector<Type>::iterator begin() { return _##attribute.begin(); } \
    std::vector<Type>::iterator end()   { return _##attribute.end(); } \
    std::vector<Type>::const_iterator begin() const { return _##attribute.begin(); } \
    std::vector<Type>::const_iterator end()   const { return _##attribute.end(); } \
    std::vector<Type>::const_iterator cbegin() const { return _##attribute.cbegin(); } \
    std::vector<Type>::const_iterator cend()   const { return _##attribute.cend(); }


#define SIZE(attribute) \
    inline size_t size() { return _##attribute.size(); }


#endif