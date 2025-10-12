# C++ Exercises — Vectors  
*Generated with OpenAI (GPT-5)*  

---

## Overview

These exercises focus on practical `std::vector` operations without using algorithms like `std::sort` or `std::find`.  
They emphasize safe access, inserting/erasing elements, and basic inspection. Loops are minimized or optional.

---

## Concepts

- Including `<vector>` and declaring `std::vector<T>`  
- Inspecting size and emptiness: `.size()`, `.empty()`  
- Element access: `operator[]`, `.at()`, `.front()`, `.back()`  
- Modifying contents: `.push_back()`, `.pop_back()`, `.insert()`, `.erase()`, `.clear()`  
- Addresses and buffer pointer: `&v[i]`, `v.data()` (read-only inspection)  
- Passing vectors to functions by const reference  
- Optional verbose mode via `-v` / `--verbose`

---

## Exercises

1. **Create and inspect (no loops)**  
   Create an empty `std::vector<double> v;`.  
   Print `v.size()` and `v.empty()` (use `std::boolalpha` so it prints `true/false`).

2. **Add elements without loops**  
   Assign `v = {1.1, 2.2, 3.3, 4.4, 5.5};` and print:  
   - `v.size()`  
   - `v.front()` and `v.back()`  
   - `v[0]` and `v.at(1)`

3. **Bounds-checked access**  
   Use `v.at(1)` to read the second element.  
   Then (commented out) add a line that would throw: `v.at(99);` and label it as “will throw”.

4. **Modify by index (no loop)**  
   Set `v[2] = 99.9;` then print `v[0]`, `v[1]`, `v[2]`, and `v.back()` to verify the change.

5. **Remove last element**  
   Call `v.pop_back();` then print `v.size()` and `v.back()` (if not empty).

6. **Insert into the middle**  
   Insert `123.456` at index `2` using `v.insert(v.begin() + 2, 123.456);`  
   Print `v[1]`, `v[2]` (inserted), and, if available, `v[3]`.

7. **Erase from the middle**  
   Erase the element at index `1` with `v.erase(v.begin() + 1);`  
   Print `v.size()` and check `v[0]` and (if available) `v[1]`.

8. **Clear the vector**  
   Call `v.clear();` then print `v.size()` and `v.empty()` (with `std::boolalpha`).

9. **Vector of ints + inspection**  
   Create `std::vector<int> numbers {10, 20, 30, 40, 50};`  
   Print `numbers.size()`, `numbers.front()`, and `numbers.back()`.  
   Write a helper function prototype:  
   ```cpp
   void inspect_vector(const std::vector<int>& v);
   ```  
   and later define it to print: the address of the vector (`&v`), `v.size()`, the buffer pointer (`static_cast<const void*>(v.data())`), and **up to the first three elements** plus `back()` (no loops required).  
   Call `inspect_vector(numbers);`

10. **Command-line verbose flag (integration)**  
    In `main(int argc, char* argv[])`, add a `-v` or `--verbose` flag that toggles extra prints.  
    When verbose is on, call `inspect_vector(numbers);` again **after** performing an `insert` and an `erase` to observe changes.

---

## Extension (optional, only if loops have been taught)

- Write a version of `inspect_vector` that uses a `for` loop to print **all** elements with their addresses.  
- Write a small manual search (with a loop) that returns whether a value exists in a vector, without using `<algorithm>`.

---

*End of file — generated with OpenAI (GPT-5)*
