# Header-only library
add_library(ProjectLib INTERFACE)
target_include_directories(ProjectLib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

# Pointers executable
add_executable(Pointers.x main.cpp)
target_link_libraries(Pointers.x PRIVATE ProjectLib)
target_compile_features(Pointers.x PRIVATE cxx_std_23)


