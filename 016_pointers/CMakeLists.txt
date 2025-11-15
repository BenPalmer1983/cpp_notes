cmake_minimum_required(VERSION 3.15)
project(Pointers VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include CTest
include(CTest) 

# Include source files
add_subdirectory(src)

# Placeholder for tests

