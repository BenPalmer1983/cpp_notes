

#include <iostream>
#include <string>
#include <vector>





class Zebra 
{

private:

    std::string _name {};
    size_t _age {};
    std::string _description;


public:


    // The Rule of Five
    // See earlier tutorial
    //
    // These are just the default constructor options (but it's going to print out, so we can see
    // what's happening when the code runs).

    // 1) Regular constructor
    // Creating a new object from scratch (using name, age)
    Zebra(const std::string& name, const size_t age, const std::string& description)  // 1) Regular 
        : _name(name), _age(age), _description(description)
    {
        std::cout << "##Default Constructor## (" << _name << " at " << std::hex << this << std::dec << ")" << std::endl;
    }


    // 2) Copy constructor            
    // Copying from another object (other)
    Zebra(const Zebra& other)
        : _name(other._name), _age(other._age), _description(other._description)
    {
        std::cout << "##Copy Constructor## (" << _name << " at " << std::hex << this << std::dec << ")" << std::endl;
    }  


    // 3) Move constructor
    // Moves from existing Zebra
    Zebra(Zebra&& other) noexcept
        : _name(std::move(other._name)), _age(std::move(other._age)), _description(std::move(other._description))
    {
        std::cout << "##Move Constructor## (" << _name << " at " << std::hex << this << std::dec << ")" << std::endl;
        other._age = 0;
    }


    // 4) Copy assignment operator
    // An existing Zebra is replaced by copying from another (other)
    Zebra& operator=(const Zebra& other)
    {
        if (this != &other) 
        {
            _name = other._name;
            _age = other._age;
            _description = other._description;
            std::cout << "##Copy Assignment## (" << _name << " at " << std::hex << this << std::dec << ")" << std::endl;
        }
        return *this;
    }


    // 5) Move assignment operator
    // An existing Zebra is replaced by moving from another (other)
    Zebra& operator=(Zebra&& other) noexcept
    {
        if (this != &other) 
        {
            _name = std::move(other._name);
            _age = std::move(other._age);
            _description = std::move(other._description);
            std::cout << "##Move Assignment## (" << _name << " at " << std::hex << this << std::dec << ")" << std::endl;
        }
        return *this;
    }

    // Destructor 
    ~Zebra()
    {
        std::cout << "##Destructor## Zebra (" << _name << " at " << std::hex << this << std::dec << ")" << std::endl;
        _name.clear(); 
        _age = 0;
        _description.clear(); 
    }


    /*
    Zebra(const std::string& name, const size_t age, const std::string& description) 
              : _name(name), _age(age), _description(description)       // regular
    Zebra(const Zebra&) = default;                                      // copy constructor
    Zebra(Zebra&&) noexcept = default;                                  // move constructor
    Zebra& operator=(const Zebra&) = default;                           // copy assignment
    Zebra& operator=(Zebra&&) noexcept = default;                       // move assignment
    ~Zebra() = default;                                                 // destructor
    */




    void set_name(const std::string& name) { _name = std::move(name); }
    void set_age(size_t age) {  _age = age; }
    const std::string& get_name() const { return _name; }
    std::string& get_name() { return _name; }
    std::string get_name_copy() const { return _name; }
    const std::string get_type() const { return "Zebra"; }
    size_t get_age() const { return _age; }

    void display() { std::cout << "Zebra:   " << _name << ", age: " << _age <<std::endl; }

};


int main()
{
    // Differences in how to add to a vector.
    std::vector<std::string> words {};

    words.push_back(std::string("Hello")); // constructs, then moves
    words.emplace_back("World");           // constructs directly in vector

    for (const auto& w : words)
    {
        std::cout << w << std::endl;
    }
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;

    {
        // Example 1 ... without reserving memory
        //               many moves/copies

        std::cout << "EXAMPLE 1.  Add without reserving space for the vector." << std::endl;
        std::cout << "##################################################################" << std::endl;


        std::vector<Zebra> zebra_pen {};

        std::cout << "Make 2 before adding." << std::endl;
        Zebra zebra_1 {"Zippy", 5, ""};
        Zebra zebra_2 {"Arthur", 7, ""};
        std::cout << "> Notice constructor called for each" << std::endl;
        std::cout << "" << std::endl;

        std::cout << "Add Zippy" << std::endl;
        zebra_pen.emplace_back(zebra_1);
        std::cout << "> Notice constructor called again for Zippy." << std::endl;
        std::cout << "> zebra_1 (Zippy) is copied into the vector." << std::endl;
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;

        std::cout << "Add Arthur" << std::endl;
        zebra_pen.emplace_back(zebra_2);
        std::cout << "> Notice Zippy is moved, Arthur is copied, " << std::endl;
        std::cout << "> the original Zippy." << std::endl;
        std::cout << "" << std::endl;

        std::cout << "Add Bertha" << std::endl;
        zebra_pen.emplace_back(Zebra{"Bertha", 8, ""});
        std::cout << "> Bertha is created and moved. " << std::endl;
        std::cout << "> The existing Zebras are also moved and cleaned up." << std::endl;
        std::cout << "" << std::endl;

        std::cout << "Add Charlie" << std::endl;
        zebra_pen.emplace_back(Zebra("Charlie", 3, ""));
        std::cout << "" << std::endl;

        std::cout << "Add Darcy" << std::endl;
        zebra_pen.push_back(Zebra{"Darcy", 8, ""});
        std::cout << "" << std::endl;

        std::cout << "Add Ernie" << std::endl;
        zebra_pen.push_back(Zebra("Ernie", 9, ""));
        std::cout << "" << std::endl;

        std::cout << "Add Forrest" << std::endl;
        zebra_pen.emplace_back(std::move(Zebra("Forrest", 11, "")));
        std::cout << "" << std::endl;

    }
    std::cout << "> Notice: cleans up at end of scope block" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    {
        // Example 2 ... with reserving memory
        //              

        std::cout << "EXAMPLE 2.  Add with reserving space for the vector." << std::endl;
        std::cout << "##################################################################" << std::endl;

        std::vector<Zebra> zebra_pen {};
        zebra_pen.reserve(7);
        std::cout << "Reserve 7." << std::endl;

        std::cout << "Make 2 before adding." << std::endl;
        Zebra zebra_1 {"Zippy", 5, ""};
        Zebra zebra_2 {"Arthur", 7, ""};

        std::cout << "Add Zippy" << std::endl;
        zebra_pen.emplace_back(zebra_1);

        std::cout << "Add Arthur" << std::endl;
        zebra_pen.emplace_back(zebra_2);

        std::cout << "Add Bertha" << std::endl;
        zebra_pen.emplace_back(Zebra{"Bertha", 8, ""});

        std::cout << "Add Charlie" << std::endl;
        zebra_pen.emplace_back(Zebra("Charlie", 3, ""));

        std::cout << "Add Darcy" << std::endl;
        zebra_pen.push_back(Zebra{"Darcy", 8, ""});

        std::cout << "Add Ernie" << std::endl;
        zebra_pen.push_back(Zebra("Ernie", 9, ""));

        std::cout << "Add Forrest" << std::endl;
        zebra_pen.emplace_back(std::move(Zebra("Forrest", 11, "")));

        std::cout << "> Notice a lot fewer moves and destructors as the vector" << std::endl;
        std::cout << "> isn't being moved to keep contiguous." << std::endl;
        std::cout << "> Still some moving, depending on how each is added to the vector." << std::endl;
        std::cout << std::endl;

    }
    std::cout << "> Notice: cleans up at end of scope block" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;


    return 0;
}

