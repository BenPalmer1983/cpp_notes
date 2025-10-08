#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>


void part_1()
{

    // useful STL algorithms with integers
    //###################################################


    std::cout << "Useful STL algorithms with integers" << std::endl;
    std::cout << "###################################################" << std::endl;
    std::cout << std::endl;


    // Test vector
    std::vector<int> nums {5, 2, 9, 1, 5, 6, 24, 3, 1, 6, 5, 12};

    // Sort
    std::cout << "Sort" << std::endl;
    std::sort(nums.begin(), nums.end());  // ascending
    for (int n : nums) 
    {
        std::cout << n << " ";
        std::cout << std::endl;
    }

    // Reverse
    std::cout << "Reverse" << std::endl;
    std::reverse(nums.begin(), nums.end());
    for (int n : nums)
    {
        std::cout << n << " ";
    } 
    std::cout << std::endl;

    // Find
    std::cout << "Find" << std::endl;
    auto it = std::find(nums.begin(), nums.end(), 5);
    if (it != nums.end())
    {
        std::cout << "Found 5 at index " << std::distance(nums.begin(), it) << std::endl;
    }

    // Count
    std::cout << "Count" << std::endl;
    int count = std::count(nums.begin(), nums.end(), 5);
    std::cout << "There are " << count << " occurrences of 5" << std::endl;

    // Accumulate
    std::cout << "Accumulate (sum)" << std::endl;
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    std::cout << "Sum = " << sum << std::endl;

    // Min
    std::cout << "Min_element" << std::endl;
    auto min_it = std::min_element(nums.begin(), nums.end());
    std::cout << "Min = " << *min_it << std::endl;

    // Max
    std::cout << "Max_element" << std::endl;
    auto max_it = std::max_element(nums.begin(), nums.end());
    std::cout << "Max = " << *max_it << std::endl;



    std::cout << "All of" << std::endl;

    bool all_positive = std::all_of(nums.begin(), nums.end(), [](int n){ return n > 0; });
    std::cout << "All positive? " << all_positive << std::endl;

    bool all_even = std::all_of(nums.begin(), nums.end(), [](int n){ return n % 2 == 0; });
    std::cout << "All even? " << all_even << std::endl;

    bool all_negative = std::all_of(nums.begin(), nums.end(), [](int n){ return n < 0; });
    std::cout << "All negative? " << all_even << std::endl;



    std::cout << "Any of" << std::endl;

    bool any_positive = std::any_of(nums.begin(), nums.end(), [](int n){ return n > 0; });
    std::cout << "Any positive? " << any_positive << std::endl;

    bool any_even = std::any_of(nums.begin(), nums.end(), [](int n){ return n % 2 == 0; });
    std::cout << "Any even? " << any_even << std::endl;

    bool any_negative = std::any_of(nums.begin(), nums.end(), [](int n){ return n < 0; });
    std::cout << "Any negative? " << any_even << std::endl;


    
    std::cout << "None of" << std::endl;

    bool none_positive = std::none_of(nums.begin(), nums.end(), [](int n){ return n > 0; });
    std::cout << "None positive? " << none_positive << std::endl;

    bool none_even = std::none_of(nums.begin(), nums.end(), [](int n){ return n % 2 == 0; });
    std::cout << "None even? " << none_even << std::endl;

    bool none_negative = std::none_of(nums.begin(), nums.end(), [](int n){ return n < 0; });
    std::cout << "None negative? " << none_even << std::endl;

    




    std::cout << "8) remove / erase idiom" << std::endl;
    nums.erase(std::remove(nums.begin(), nums.end(), 5), nums.end());
    for (int n : nums)
    {
        std::cout << n << " ";
    } 
    std::cout << std::endl;

    std::cout << "9) unique" << std::endl;
    std::vector<int> vals {1,1,2,2,2,3,3,4};
    vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
    for (int v : vals)
    {
        std::cout << v << " ";     
    } 
    std::cout << std::endl;

    std::cout << "10) transform" << std::endl;
    std::vector<int> squares(nums.size());
    std::transform(nums.begin(), nums.end(), squares.begin(), [](int n){ return n*n; });
    for (int s : squares) std::cout << s << " ";
    std::cout << std::endl;

    std::cout << "11) for_each" << std::endl;
    std::for_each(nums.begin(), nums.end(), [](int n){ std::cout << "[" << n << "] "; });
    std::cout << std::endl;










    std::cout << "12) partition" << std::endl;
    std::vector<int> mixed {1,2,3,4,5,6,7,8,9};
    std::partition(mixed.begin(), mixed.end(), [](int n){ return n % 2 == 0; });
    for (int m : mixed) std::cout << m << " ";
    std::cout << std::endl;

    std::cout << "13) binary_search (on sorted data)" << std::endl;
    std::sort(mixed.begin(), mixed.end());
    bool found4 = std::binary_search(mixed.begin(), mixed.end(), 4);
    std::cout << "Found 4? " << found4 << std::endl;

    std::cout << "14) next_permutation" << std::endl;
    std::vector<int> perm {1,2,3};
    do
    {
        for (int p : perm) std::cout << p;
        std::cout << " ";
    }
    while (std::next_permutation(perm.begin(), perm.end()));
    std::cout << std::endl;


}