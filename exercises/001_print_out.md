# C++ Exercises — Hello World  
*Generated with OpenAI (GPT-5)*  

---

## Overview

These exercises are based on **HelloWorld.cpp** and are designed to introduce you to basic C++ syntax, program structure, and console output.

---

## Concepts

- Program structure (`main` function)
- Output using `std::cout`
- Newline characters and formatting

---

## Exercises

1. **Print your name**  
   Modify the program to print your name instead of `Hello World`.

2. **Add another line**  
   Print a second line saying:  

   Welcome to C++ programming!

3. **Experiment with `std::endl`**  
Replace `std::endl` with `"\n"`.  
What difference do you observe?

4. **Multiple outputs on one line**  
Print `"Hello"` and `"World"` using **two `std::cout` statements**, but keep them on the **same line**.

---

## Extension

Try combining text and variables in your output:
```cpp
std::string name = "Alice";
std::cout << "Hello, " << name << "!" << std::endl;
