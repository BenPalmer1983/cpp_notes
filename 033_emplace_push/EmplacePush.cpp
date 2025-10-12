

#include <iostream>
#include <string>
#include <vector>





class Zebra 
{

private:

    std::string _name {};
    size_t _age {};


public:

    // Direct constructor
    Zebra (const std::string& name, size_t age) :  _name(name), _age(age) { std::cout << "  Constructing  "; display(); }
    // Copy constructor
    Zebra (const Zebra& other) :  _name(other.get_name()), _age(other.get_age()) { std::cout << "  Copying  "; display(); }
    // Move constructor
    Zebra (Zebra&& other) noexcept : _name{std::move(other.get_name())}, _age{other.get_age()} { std::cout << "  Moving  "; display(); }





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
    std::vector<std::string> words {};

    words.push_back(std::string("Hello")); // constructs, then moves
    words.emplace_back("World");           // constructs directly in vector

    for (const auto& w : words)
    {
        std::cout << w << std::endl;
    }

    {
        // Example 1 ... without reserving memory
        //               many moves/copies

        std::vector<Zebra> zebra_pen {};

        std::cout << "Make 2 before adding." << std::endl;
        Zebra zebra_1 {"Zippy", 5};
        Zebra zebra_2 {"Arthur", 7};

        std::cout << "Add Zippy" << std::endl;
        zebra_pen.emplace_back(zebra_1);

        std::cout << "Add Arthur" << std::endl;
        zebra_pen.emplace_back(zebra_2);

        std::cout << "Add Bertha" << std::endl;
        zebra_pen.emplace_back(Zebra{"Bertha", 8});

        std::cout << "Add Charlie" << std::endl;
        zebra_pen.emplace_back(Zebra("Charlie", 3));

        std::cout << "Add Darcy" << std::endl;
        zebra_pen.push_back(Zebra{"Darcy", 8});

        std::cout << "Add Ernie" << std::endl;
        zebra_pen.push_back(Zebra("Ernie", 9));

        std::cout << "Add Forrest" << std::endl;
        zebra_pen.emplace_back(std::move(Zebra("Forrest", 11)));

    }

    std::cout << std::endl;

    {
        // Example 2 ... with reserving memory
        //              

        std::vector<Zebra> zebra_pen {};
        zebra_pen.reserve(7);

        std::cout << "Make 2 before adding." << std::endl;
        Zebra zebra_1 {"Zippy", 5};
        Zebra zebra_2 {"Arthur", 7};

        std::cout << "Add Zippy" << std::endl;
        zebra_pen.emplace_back(zebra_1);

        std::cout << "Add Arthur" << std::endl;
        zebra_pen.emplace_back(zebra_2);

        std::cout << "Add Bertha" << std::endl;
        zebra_pen.emplace_back(Zebra{"Bertha", 8});

        std::cout << "Add Charlie" << std::endl;
        zebra_pen.emplace_back(Zebra("Charlie", 3));

        std::cout << "Add Darcy" << std::endl;
        zebra_pen.push_back(Zebra{"Darcy", 8});

        std::cout << "Add Ernie" << std::endl;
        zebra_pen.push_back(Zebra("Ernie", 9));

        std::cout << "Add Forrest" << std::endl;
        zebra_pen.emplace_back(std::move(Zebra("Forrest", 11)));

    }


    return 0;
}

