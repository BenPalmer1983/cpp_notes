cmake_minimum_required(VERSION 3.20)
project(Vec3Struct VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_subdirectory(src)


enable_testing()
set(INSTALL_GTEST OFF CACHE BOOL "Disable gtest install" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(
    ../external/googletest
    ${CMAKE_BINARY_DIR}/external/googletest
)
add_subdirectory(src_tests)
