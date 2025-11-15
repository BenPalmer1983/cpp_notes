
#include <iostream>
#include <vector>
#include <string>
#include <chrono>




// https://www.youtube.com/watch?v=xnqTKD8uD64
int main()
{
    



    /*
    1) correctness - always the right type
    2) correctness and maintainability
    3) performance - no conversions
    4) usability
    5) convenience
    */





    {
        int i = 42;
        int j = 42.0;     // silent narrowing
        float x = 42.0;
        double y = 42.0;
    }



    // "Modern" way, use auto.
    {
        auto i = 42;
        auto j = 42;
        auto k = 42u;                // unsigned int
        auto n = std::size_t{42};    // 64bit size
        auto x = 42.0f;
        auto y = 42.0;
    }

    // If you prefer explicit, use braces to avoid narrowing
    {
        int i {42};
        // int j {42.0};     // would now throw exception
        float x {42.0};
        double y {42.0};
    }


    {
        auto name_a = std::string("This is a name");
        
    }

    {
        auto t = std::chrono::nanoseconds {42};
        
    }


}

void test_1(const std::vector<int>& v)
{
    //  std::vector<int>::iterator it = v.begin();          // would error at compile
    // std::vector<int>::const_iterator it = v.begin();     // works
    auto it = v.begin();                                    // maintainable, correct

}


void test_2(std::vector<int>& v)
{
    //std::vector<int>::iterator it = v.begin();            // works
    //std::vector<int>::const_iterator it = v.begin();      // works
    auto it = v.begin();                                    // maintainable, correct
    const auto const_it = v.begin();                              // maintainable, correct

}


