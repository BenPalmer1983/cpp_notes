
# Header-only library

add_library(ProjectLib INTERFACE)
target_include_directories(ProjectLib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)