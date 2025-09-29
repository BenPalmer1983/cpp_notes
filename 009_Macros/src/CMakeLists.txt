
# Header-only library

add_library(ProjectLib INTERFACE)
target_include_directories(ProjectLib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)


add_executable(Macros.x main.cpp)
target_link_libraries(Macros.x PRIVATE ProjectLib)
target_compile_features(Macros.x PRIVATE cxx_std_20)
